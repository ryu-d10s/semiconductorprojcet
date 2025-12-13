#############################
#   @author: Nitin Rathi    #
#############################
import argparse
import torch
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torchvision import datasets, transforms
from tqdm import tqdm
import sys
import datetime
import os
import numpy as np
from sklearn.model_selection import KFold # Import KFold
from torch.utils.data import ConcatDataset, SubsetRandomSampler # Import data tools
from self_models import *
from torchinfo import summary as summary_info

class AverageMeter(object):
    """Computes and stores the average and current value"""
    def __init__(self, name, fmt=':f'):
        self.name = name
        self.fmt = fmt
        self.reset()

    def reset(self):
        self.val = 0
        self.avg = 0
        self.sum = 0
        self.count = 0

    def update(self, val, n=1):
        self.val = val
        self.sum += val * n
        self.count += n
        self.avg = self.sum / self.count

    def __str__(self):
        fmtstr = '{name} {val' + self.fmt + '} ({avg' + self.fmt + '})'
        return fmtstr.format(**self.__dict__)

def train(epoch, loader):
    # Relies on global 'model', 'optimizer', 'learning_rate', 'f'
    global learning_rate
    
    losses = AverageMeter('Loss')
    top1   = AverageMeter('Acc@1')

    # Note: lr_interval check moved to main loop or kept here if global lr_interval is updated correctly
    if epoch in lr_interval:
        for param_group in optimizer.param_groups:
            param_group['lr'] = param_group['lr'] / lr_reduce
            learning_rate = param_group['lr']
    
    model.train()
    pbar = tqdm(enumerate(loader), total=len(loader), desc=f"Train", unit="batch")
    for batch_idx, (data, target) in pbar:
        
        start_time = datetime.datetime.now()

        if torch.cuda.is_available() and args.gpu:
            data, target = data.cuda(), target.cuda()
                
        optimizer.zero_grad()
        output = model(data)
        loss = F.cross_entropy(output,target)
        loss.backward()
        optimizer.step()
        pred = output.max(1,keepdim=True)[1]
        correct = pred.eq(target.data.view_as(pred)).cpu().sum()

        losses.update(loss.item(), data.size(0))
        top1.update(correct.item()/data.size(0), data.size(0))
        pbar.set_postfix({'Loss': f'{losses.avg:.4f}', 'Acc': f'{100*top1.avg:.2f}', 'LR': f'{learning_rate:.1e}'})
        
    f.write('\n Epoch: {}, lr: {:.1e}, train_loss: {:.4f}, train_acc: {:.4f}'.format(
            epoch,
            learning_rate,
            losses.avg,
            top1.avg
            )
        )

def test(loader):
    # Relies on global 'model', 'max_accuracy', 'start_time', 'f'
    losses = AverageMeter('Loss')
    top1   = AverageMeter('Acc@1')

    with torch.no_grad():
        model.eval()
        total_loss = 0
        correct = 0
        global max_accuracy, start_time
        
        pbar = tqdm(enumerate(loader), total=len(loader), desc=f"Test", unit="batch")
        
        for batch_idx, (data, target) in pbar:
                        
            if torch.cuda.is_available() and args.gpu:
                data, target = data.cuda(), target.cuda()
            
            output = model(data)
            loss = F.cross_entropy(output,target)
            total_loss += loss.item()
            pred = output.max(1, keepdim=True)[1]
            correct = pred.eq(target.data.view_as(pred)).cpu().sum()
            losses.update(loss.item(), data.size(0))
            top1.update(correct.item()/data.size(0), data.size(0))

            pbar.set_postfix({'Loss': f'{losses.avg:.4f}', 'Acc': f'{100*top1.avg:.2f}'})

        # Early stopping logic (optional to keep or remove for CV)
        if epoch>30 and top1.avg<0.15:
            f.write('\n Quitting as the training is not progressing')
            # In CV, maybe don't exit entire script, just break loop? 
            # For now keeping as is but be warned it kills the whole run.
            # exit(0) 
            pass

        if top1.avg>max_accuracy:
            max_accuracy = top1.avg
            state = {
                    'accuracy'      : max_accuracy,
                    'epoch'         : epoch,
                    'state_dict'    : model.state_dict(),
                    'optimizer'     : optimizer.state_dict()
            }
            try:
                os.mkdir('./trained_models/ann/')
            except OSError:
                pass
            
            # Update filename to include Fold info if possible, or just overwrite best
            filename = './trained_models/ann/'+identifier+'.pth'
            torch.save(state,filename)
            
        f.write(' test_loss: {:.4f}, test_acc: {:.4f}, best: {:.4f}, time: {}'.  format(
            losses.avg, 
            top1.avg,
            max_accuracy,
            datetime.timedelta(seconds=(datetime.datetime.now() - start_time).seconds)
            )
        )

if __name__ == '__main__':
    torch.multiprocessing.set_start_method('spawn', force=True)
    parser = argparse.ArgumentParser(description='Train ANN 10-Fold CV', formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    # ... (Keep all your existing arguments) ...
    parser.add_argument('--gpu',                    default=True,               type=bool,      help='use gpu')
    parser.add_argument('--log',                    action='store_true',                        help='to print the output on terminal or to log file')
    parser.add_argument('-s','--seed',              default=0,                  type=int,       help='seed for random number')
    parser.add_argument('--dataset',                default='CIFAR10',          type=str,       help='dataset name', choices=['MNIST','CIFAR10','CIFAR100','HAND_GESTURE'])
    parser.add_argument('--batch_size',             default=64,                 type=int,       help='minibatch size')
    parser.add_argument('-a','--architecture',      default='VGG16',            type=str,       help='network architecture', choices=['VGG5','VGG9','VGG11','VGG13','VGG16','VGG19','RESNET12','RESNET20','RESNET34'])
    parser.add_argument('-lr','--learning_rate',    default=1e-2,               type=float,     help='initial learning_rate')
    parser.add_argument('--pretrained_ann',         default='',                 type=str,       help='pretrained model to initialize ANN')
    parser.add_argument('--test_only',              action='store_true',                        help='perform only inference')
    parser.add_argument('--epochs',                 default=300,                type=int,       help='number of training epochs')
    parser.add_argument('--lr_interval',            default='0.60 0.80 0.90',   type=str,       help='intervals at which to reduce lr, expressed as %%age of total epochs')
    parser.add_argument('--lr_reduce',              default=10,                 type=int,       help='reduction factor for learning rate')
    parser.add_argument('--optimizer',              default='SGD',              type=str,       help='optimizer for SNN backpropagation', choices=['SGD', 'Adam'])
    parser.add_argument('--weight_decay',           default=5e-4,               type=float,     help='weight decay parameter for the optimizer')
    parser.add_argument('--momentum',               default=0.9,                type=float,     help='momentum parameter for the SGD optimizer')
    parser.add_argument('--amsgrad',                default=True,               type=bool,      help='amsgrad parameter for Adam optimizer')
    parser.add_argument('--dropout',                default=0.2,                type=float,     help='dropout percentage for conv layers')
    parser.add_argument('--kernel_size',            default=3,                  type=int,       help='filter size for the conv layers')
    parser.add_argument('--devices',                default='0',                type=str,       help='list of gpu device(s)')
    parser.add_argument('--k_folds',                default=10,                 type=int,       help='number of folds for cross validation')
        
    args=parser.parse_args()

    os.environ['CUDA_VISIBLE_DEVICES'] = args.devices
    
    # Seed random number
    torch.manual_seed(args.seed)
    np.random.seed(args.seed)
    torch.cuda.manual_seed(args.seed)
    torch.cuda.manual_seed_all(args.seed)
    
    dataset         = args.dataset
    batch_size      = args.batch_size
    architecture    = args.architecture
    pretrained_ann  = args.pretrained_ann
    epochs          = args.epochs
    lr_reduce       = args.lr_reduce
    weight_decay    = args.weight_decay
    momentum        = args.momentum
    amsgrad         = args.amsgrad
    dropout         = args.dropout
    kernel_size     = args.kernel_size

    # Parse LR interval
    values = args.lr_interval.split()
    lr_interval_base = []
    for value in values:
        lr_interval_base.append(int(float(value)*args.epochs))
    
    log_file = './logs/ann/'
    try:
        os.mkdir(log_file)
    except OSError:
        pass 
    
    identifier = 'ann_'+architecture.lower()+'_'+dataset.lower()+'_'+str(datetime.datetime.now())
    log_file+=identifier+'.log'
    
    if args.log:
        f= open(log_file, 'w', buffering=1)
    else:
        f=sys.stdout
    
    f.write('\n Run on time: {}'.format(datetime.datetime.now()))
    f.write('\n\n Arguments:')
    for arg in vars(args):
        f.write('\n\t {:20} : {}'.format(arg, getattr(args,arg)))
        
    if torch.cuda.is_available() and args.gpu:
        torch.set_default_tensor_type('torch.cuda.FloatTensor')
    
    # --- DATASET LOADING (MODIFIED FOR CV) ---
    # We load datasets twice: once with train transforms (for training folds) 
    # and once with test transforms (for validation folds).
    
    if dataset == 'CIFAR100':
        normalize   = transforms.Normalize((0.5071,0.4867,0.4408),(0.2675,0.2565,0.2761))
        labels      = 100 
    elif dataset == 'CIFAR10':
        normalize   = transforms.Normalize((0.4914, 0.4822, 0.4465), (0.2023, 0.1994, 0.2010))
        labels      = 10
    elif dataset == 'MNIST':
        labels = 10
    
    # Define Transforms
    if dataset == 'CIFAR10' or dataset == 'CIFAR100':
        transform_train = transforms.Compose([
            transforms.RandomCrop(32, padding=4),
            transforms.RandomHorizontalFlip(),
            transforms.ToTensor(),
            normalize
        ])
        transform_test = transforms.Compose([transforms.ToTensor(), normalize])
        
    elif dataset == 'HAND_GESTURE':
        normalize = transforms.Normalize(mean=[0.5], std=[0.5])
        transform_train = transforms.Compose([
            transforms.Grayscale(num_output_channels=1),
            transforms.Resize((64, 64)),
            transforms.RandomHorizontalFlip(),
            transforms.RandomRotation(10),
            transforms.ToTensor(),
            normalize
        ])
        transform_test = transforms.Compose([
            transforms.Grayscale(num_output_channels=1),
            transforms.Resize((64, 64)),
            transforms.ToTensor(),
            normalize
        ])
    
    # Load ALL data (Both Train=True and Train=False merged)
    if dataset == 'CIFAR100':
        d1 = datasets.CIFAR100(root='~/Datasets/cifar_data', train=True, download=True, transform=transform_train)
        d2 = datasets.CIFAR100(root='~/Datasets/cifar_data', train=False, download=True, transform=transform_train)
        dataset_for_train_folds = ConcatDataset([d1, d2])

        d1_test = datasets.CIFAR100(root='~/Datasets/cifar_data', train=True, download=True, transform=transform_test)
        d2_test = datasets.CIFAR100(root='~/Datasets/cifar_data', train=False, download=True, transform=transform_test)
        dataset_for_test_folds = ConcatDataset([d1_test, d2_test])
    
    elif dataset == 'CIFAR10': 
        d1 = datasets.CIFAR10(root='~/Datasets/cifar_data', train=True, download=True, transform=transform_train)
        d2 = datasets.CIFAR10(root='~/Datasets/cifar_data', train=False, download=True, transform=transform_train)
        dataset_for_train_folds = ConcatDataset([d1, d2])

        d1_test = datasets.CIFAR10(root='~/Datasets/cifar_data', train=True, download=True, transform=transform_test)
        d2_test = datasets.CIFAR10(root='~/Datasets/cifar_data', train=False, download=True, transform=transform_test)
        dataset_for_test_folds = ConcatDataset([d1_test, d2_test])
    
    elif dataset == 'MNIST':
        d1 = datasets.MNIST(root='~/Datasets/mnist/', train=True, download=True, transform=transforms.ToTensor())
        d2 = datasets.MNIST(root='~/Datasets/mnist/', train=False, download=True, transform=transforms.ToTensor())
        # MNIST doesn't heavily rely on augmentation in your code, so we can use same for both usually, 
        # but following pattern:
        dataset_for_train_folds = ConcatDataset([d1, d2])
        dataset_for_test_folds = ConcatDataset([d1, d2])
    
    elif dataset == 'HAND_GESTURE':
        d1 = datasets.ImageFolder(root='./Datasets/hand_gesture/train', transform=transform_train)
        d2 = datasets.ImageFolder(root='./Datasets/hand_gesture/test', transform=transform_train)
        dataset_for_train_folds = ConcatDataset([d1, d2])

        d1_test = datasets.ImageFolder(root='./Datasets/hand_gesture/train', transform=transform_test)
        d2_test = datasets.ImageFolder(root='./Datasets/hand_gesture/test', transform=transform_test)
        dataset_for_test_folds = ConcatDataset([d1_test, d2_test])
        
        labels = len(d1.classes) # Assuming classes are same in both folders

    # --- K-FOLD CROSS VALIDATION LOOP ---
    kfold = KFold(n_splits=args.k_folds, shuffle=True, random_state=args.seed)
    
    # We use indices from one of the datasets (they are same size)
    total_indices = np.arange(len(dataset_for_train_folds))
    
    f.write(f'\n\nStarting {args.k_folds}-Fold Cross Validation')

    results = {}

    for fold, (train_ids, test_ids) in enumerate(kfold.split(total_indices)):
        f.write(f'\n\n---------------- FOLD {fold + 1}/{args.k_folds} ----------------')
        print(f'\nFOLD {fold + 1}/{args.k_folds}')
        
        # Reset Global Variables specific to a training run
        learning_rate = args.learning_rate
        lr_interval = lr_interval_base # Reset LR schedule
        max_accuracy = 0
        
        # Create Samplers
        train_subsampler = SubsetRandomSampler(train_ids)
        test_subsampler = SubsetRandomSampler(test_ids)
        
        # Create DataLoaders
        # Note: dataset_for_train_folds has Augmentation, dataset_for_test_folds has Clean
        train_loader = torch.utils.data.DataLoader(
            dataset_for_train_folds, 
            batch_size=batch_size, 
            sampler=train_subsampler, # Use Sampler
            num_workers=4,
            generator=torch.Generator(device='cuda') if device.type == 'cuda' else None
        )
        
        test_loader = torch.utils.data.DataLoader(
            dataset_for_test_folds, 
            batch_size=batch_size, 
            sampler=test_subsampler, # Use Sampler
            num_workers=4,
            generator=torch.Generator(device='cuda') if device.type == 'cuda' else None
        )

        # --- MODEL INITIALIZATION (MUST BE DONE EVERY FOLD) ---
        if architecture[0:3].lower() == 'vgg':
            model = VGG(vgg_name=architecture, labels=labels, dataset=dataset, kernel_size=kernel_size, dropout=dropout)
        elif architecture[0:3].lower() == 'res':
            if architecture.lower() == 'resnet12':
                model = ResNet12(labels=labels, dropout=dropout)
            elif architecture.lower() == 'resnet20':
                model = ResNet20(labels=labels, dropout=dropout)
            elif architecture.lower() == 'resnet34':
                model = ResNet34(labels=labels, dropout=dropout) 
        
        model = nn.DataParallel(model)
        
        # Load Pretrained if exists (Note: In CV, this might bias results if pretrained on same data, assuming external pretraining)
        if args.pretrained_ann:
            state=torch.load(args.pretrained_ann, map_location='cpu')
            cur_dict = model.state_dict()
            for key in state['state_dict'].keys():
                if key in cur_dict:
                    if (state['state_dict'][key].shape == cur_dict[key].shape):
                        cur_dict[key] = nn.Parameter(state['state_dict'][key].data)
                    else:
                        f.write('\n Error: Size mismatch...')
            model.load_state_dict(cur_dict)
            f.write('\n Loaded pretrained model for Fold {}'.format(fold+1))
            
            # Determine input size (batch_size, channels, h, w)
        if dataset == 'MNIST':
            input_size = (batch_size, 1, 28, 28)
        elif dataset == 'HAND_GESTURE':
            input_size = (batch_size, 1, 64, 64)
        else:
            input_size = (batch_size, 3, 32, 32)

        model_stats = summary_info(model, input_size=input_size, verbose=0)
        print(model_stats) # Print to console
        f.write('\n{}'.format(model_stats)) # Write clean summary to your log file

        if torch.cuda.is_available() and args.gpu:
            model.cuda()
        
        # Reset Optimizer
        optimizer_name = args.optimizer # local var to avoid conflict
        if optimizer_name == 'SGD':
            optimizer = optim.SGD(model.parameters(), lr=learning_rate, momentum=momentum, weight_decay=weight_decay)
        elif optimizer_name == 'Adam':
            optimizer = optim.Adam(model.parameters(), lr=learning_rate, amsgrad=amsgrad, weight_decay=weight_decay)
        
        # --- EPOCH LOOP ---
        for epoch in range(1, epochs + 1):
            start_time = datetime.datetime.now()
            print(f"Epoch {epoch}")
            train(epoch, train_loader)
            test(test_loader)
        
        # Store result for this fold
        results[fold] = max_accuracy
        f.write(f'\n Fold {fold+1} Best Accuracy: {max_accuracy:.4f}')

    # Summary
    f.write('\n\n================ CROSS VALIDATION SUMMARY ================')
    avg_acc = sum(results.values()) / len(results)
    f.write(f'\n Average Accuracy over {args.k_folds} folds: {avg_acc:.4f}')
    for fold, acc in results.items():
        f.write(f'\n Fold {fold+1}: {acc:.4f}')