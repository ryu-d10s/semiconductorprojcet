#include "snn_core_fc_last.h"
#include "AESL_pkg.h"

using namespace std;

namespace ap_rtl {

void snn_core_fc_last::thread_icmp_ln67_fu_5376_p2() {
    icmp_ln67_fu_5376_p2 = (!ap_phi_mux_o1_0_phi_fu_5104_p4.read().is_01() || !ap_const_lv4_A.is_01())? sc_lv<1>(): sc_lv<1>(ap_phi_mux_o1_0_phi_fu_5104_p4.read() == ap_const_lv4_A);
}

void snn_core_fc_last::thread_icmp_ln883_fu_5356_p2() {
    icmp_ln883_fu_5356_p2 = (!v_V_fu_5352_p1.read().is_01() || !ap_const_lv8_0.is_01())? sc_lv<1>(): sc_lv<1>(v_V_fu_5352_p1.read() != ap_const_lv8_0);
}

void snn_core_fc_last::thread_icmp_ln88_fu_9036_p2() {
    icmp_ln88_fu_9036_p2 = (!ap_phi_mux_max_idx_phi_fu_5137_p4.read().is_01() || !ap_const_lv4_A.is_01())? sc_lv<1>(): sc_lv<1>(ap_phi_mux_max_idx_phi_fu_5137_p4.read() == ap_const_lv4_A);
}

void snn_core_fc_last::thread_icmp_ln90_1_fu_9095_p2() {
    icmp_ln90_1_fu_9095_p2 = (!trunc_ln90_fu_9067_p1.read().is_01() || !ap_const_lv23_0.is_01())? sc_lv<1>(): sc_lv<1>(trunc_ln90_fu_9067_p1.read() == ap_const_lv23_0);
}

void snn_core_fc_last::thread_icmp_ln90_2_fu_9101_p2() {
    icmp_ln90_2_fu_9101_p2 = (!tmp_4_fu_9075_p4.read().is_01() || !ap_const_lv8_FF.is_01())? sc_lv<1>(): sc_lv<1>(tmp_4_fu_9075_p4.read() != ap_const_lv8_FF);
}

void snn_core_fc_last::thread_icmp_ln90_3_fu_9107_p2() {
    icmp_ln90_3_fu_9107_p2 = (!trunc_ln90_1_fu_9085_p1.read().is_01() || !ap_const_lv23_0.is_01())? sc_lv<1>(): sc_lv<1>(trunc_ln90_1_fu_9085_p1.read() == ap_const_lv23_0);
}

void snn_core_fc_last::thread_icmp_ln90_fu_9089_p2() {
    icmp_ln90_fu_9089_p2 = (!tmp_fu_9057_p4.read().is_01() || !ap_const_lv8_FF.is_01())? sc_lv<1>(): sc_lv<1>(tmp_fu_9057_p4.read() != ap_const_lv8_FF);
}

void snn_core_fc_last::thread_in_stream_TDATA_blk_n() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state5.read()) && 
         esl_seteq<1,1,1>(icmp_ln57_fu_5336_p2.read(), ap_const_lv1_0))) {
        in_stream_TDATA_blk_n = in_stream_TVALID.read();
    } else {
        in_stream_TDATA_blk_n = ap_const_logic_1;
    }
}

void snn_core_fc_last::thread_in_stream_TREADY() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state5.read()) && 
         esl_seteq<1,1,1>(icmp_ln57_fu_5336_p2.read(), ap_const_lv1_0) && 
         !(esl_seteq<1,1,1>(icmp_ln57_fu_5336_p2.read(), ap_const_lv1_0) && esl_seteq<1,1,1>(ap_const_logic_0, in_stream_TVALID.read())))) {
        in_stream_TREADY = ap_const_logic_1;
    } else {
        in_stream_TREADY = ap_const_logic_0;
    }
}

void snn_core_fc_last::thread_max_idx_1_fu_9144_p3() {
    max_idx_1_fu_9144_p3 = (!and_ln90_1_fu_9131_p2.read()[0].is_01())? sc_lv<32>(): ((and_ln90_1_fu_9131_p2.read()[0].to_bool())? zext_ln88_fu_9113_p1.read(): output_class_write_a_reg_5121.read());
}

void snn_core_fc_last::thread_max_val_2_fu_9137_p3() {
    max_val_2_fu_9137_p3 = (!and_ln90_1_fu_9131_p2.read()[0].is_01())? sc_lv<32>(): ((and_ln90_1_fu_9131_p2.read()[0].to_bool())? max_val_1_reg_14594.read(): max_val_0_reg_5111.read());
}

void snn_core_fc_last::thread_mem_address0() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_pp2_stage13.read()) && 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_enable_reg_pp2_iter10.read()) && 
         esl_seteq<1,1,1>(ap_block_pp2_stage13.read(), ap_const_boolean_0))) {
        mem_address0 = mem_addr_1_reg_12019_pp2_iter10_reg.read();
    } else if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_enable_reg_pp2_iter0.read()) && 
                esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_pp2_stage0.read()) && 
                esl_seteq<1,1,1>(ap_block_pp2_stage0.read(), ap_const_boolean_0))) {
        mem_address0 =  (sc_lv<4>) (zext_ln74_fu_5388_p1.read());
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        mem_address0 =  (sc_lv<4>) (zext_ln44_fu_5318_p1.read());
    } else {
        mem_address0 =  (sc_lv<4>) ("XXXX");
    }
}

void snn_core_fc_last::thread_mem_ce0() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) || 
         (esl_seteq<1,1,1>(ap_const_logic_1, ap_enable_reg_pp2_iter0.read()) && 
          esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_pp2_stage0.read()) && 
          esl_seteq<1,1,1>(ap_block_pp2_stage0_11001.read(), ap_const_boolean_0)) || 
         (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_pp2_stage13.read()) && 
          esl_seteq<1,1,1>(ap_block_pp2_stage13_11001.read(), ap_const_boolean_0) && 
          esl_seteq<1,1,1>(ap_const_logic_1, ap_enable_reg_pp2_iter10.read())))) {
        mem_ce0 = ap_const_logic_1;
    } else {
        mem_ce0 = ap_const_logic_0;
    }
}

void snn_core_fc_last::thread_mem_d0() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_pp2_stage13.read()) && 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_enable_reg_pp2_iter10.read()) && 
         esl_seteq<1,1,1>(ap_block_pp2_stage13.read(), ap_const_boolean_0))) {
        mem_d0 = select_ln16_fu_9020_p3.read();
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        mem_d0 = ap_const_lv32_0;
    } else {
        mem_d0 =  (sc_lv<32>) ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    }
}

void snn_core_fc_last::thread_mem_we0() {
    if (((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
          esl_seteq<1,1,1>(ap_const_lv1_0, icmp_ln42_fu_5306_p2.read())) || 
         (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_pp2_stage13.read()) && 
          esl_seteq<1,1,1>(ap_block_pp2_stage13_11001.read(), ap_const_boolean_0) && 
          esl_seteq<1,1,1>(ap_const_logic_1, ap_enable_reg_pp2_iter10.read()) && 
          esl_seteq<1,1,1>(ap_const_lv1_0, icmp_ln67_reg_11742_pp2_iter10_reg.read())))) {
        mem_we0 = ap_const_logic_1;
    } else {
        mem_we0 = ap_const_logic_0;
    }
}

void snn_core_fc_last::thread_o_1_fu_9047_p2() {
    o_1_fu_9047_p2 = (!ap_const_lv4_1.is_01() || !ap_phi_mux_max_idx_phi_fu_5137_p4.read().is_01())? sc_lv<4>(): (sc_biguint<4>(ap_const_lv4_1) + sc_biguint<4>(ap_phi_mux_max_idx_phi_fu_5137_p4.read()));
}

void snn_core_fc_last::thread_o_2_fu_5382_p2() {
    o_2_fu_5382_p2 = (!ap_phi_mux_o1_0_phi_fu_5104_p4.read().is_01() || !ap_const_lv4_1.is_01())? sc_lv<4>(): (sc_biguint<4>(ap_phi_mux_o1_0_phi_fu_5104_p4.read()) + sc_biguint<4>(ap_const_lv4_1));
}

void snn_core_fc_last::thread_o_fu_5312_p2() {
    o_fu_5312_p2 = (!o_0_reg_5067.read().is_01() || !ap_const_lv4_1.is_01())? sc_lv<4>(): (sc_biguint<4>(o_0_reg_5067.read()) + sc_biguint<4>(ap_const_lv4_1));
}

void snn_core_fc_last::thread_or_ln16_fu_9008_p2() {
    or_ln16_fu_9008_p2 = (icmp_ln16_1_fu_9002_p2.read() | icmp_ln16_fu_8996_p2.read());
}

void snn_core_fc_last::thread_or_ln74_100_fu_6808_p2() {
    or_ln74_100_fu_6808_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_65);
}

void snn_core_fc_last::thread_or_ln74_101_fu_6822_p2() {
    or_ln74_101_fu_6822_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_66);
}

void snn_core_fc_last::thread_or_ln74_102_fu_6836_p2() {
    or_ln74_102_fu_6836_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_67);
}

void snn_core_fc_last::thread_or_ln74_103_fu_6850_p2() {
    or_ln74_103_fu_6850_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_68);
}

void snn_core_fc_last::thread_or_ln74_104_fu_6864_p2() {
    or_ln74_104_fu_6864_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_69);
}

void snn_core_fc_last::thread_or_ln74_105_fu_6878_p2() {
    or_ln74_105_fu_6878_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_6A);
}

void snn_core_fc_last::thread_or_ln74_106_fu_6892_p2() {
    or_ln74_106_fu_6892_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_6B);
}

void snn_core_fc_last::thread_or_ln74_107_fu_6906_p2() {
    or_ln74_107_fu_6906_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_6C);
}

void snn_core_fc_last::thread_or_ln74_108_fu_6920_p2() {
    or_ln74_108_fu_6920_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_6D);
}

void snn_core_fc_last::thread_or_ln74_109_fu_6934_p2() {
    or_ln74_109_fu_6934_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_6E);
}

void snn_core_fc_last::thread_or_ln74_10_fu_5548_p2() {
    or_ln74_10_fu_5548_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_B);
}

void snn_core_fc_last::thread_or_ln74_110_fu_6948_p2() {
    or_ln74_110_fu_6948_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_6F);
}

void snn_core_fc_last::thread_or_ln74_111_fu_6962_p2() {
    or_ln74_111_fu_6962_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_70);
}

void snn_core_fc_last::thread_or_ln74_112_fu_6976_p2() {
    or_ln74_112_fu_6976_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_71);
}

void snn_core_fc_last::thread_or_ln74_113_fu_6990_p2() {
    or_ln74_113_fu_6990_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_72);
}

void snn_core_fc_last::thread_or_ln74_114_fu_7004_p2() {
    or_ln74_114_fu_7004_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_73);
}

void snn_core_fc_last::thread_or_ln74_115_fu_7018_p2() {
    or_ln74_115_fu_7018_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_74);
}

void snn_core_fc_last::thread_or_ln74_116_fu_7032_p2() {
    or_ln74_116_fu_7032_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_75);
}

void snn_core_fc_last::thread_or_ln74_117_fu_7046_p2() {
    or_ln74_117_fu_7046_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_76);
}

void snn_core_fc_last::thread_or_ln74_118_fu_7060_p2() {
    or_ln74_118_fu_7060_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_77);
}

void snn_core_fc_last::thread_or_ln74_119_fu_7074_p2() {
    or_ln74_119_fu_7074_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_78);
}

void snn_core_fc_last::thread_or_ln74_11_fu_5562_p2() {
    or_ln74_11_fu_5562_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_C);
}

void snn_core_fc_last::thread_or_ln74_120_fu_7088_p2() {
    or_ln74_120_fu_7088_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_79);
}

void snn_core_fc_last::thread_or_ln74_121_fu_7102_p2() {
    or_ln74_121_fu_7102_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_7A);
}

void snn_core_fc_last::thread_or_ln74_122_fu_7116_p2() {
    or_ln74_122_fu_7116_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_7B);
}

void snn_core_fc_last::thread_or_ln74_123_fu_7130_p2() {
    or_ln74_123_fu_7130_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_7C);
}

void snn_core_fc_last::thread_or_ln74_124_fu_7144_p2() {
    or_ln74_124_fu_7144_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_7D);
}

void snn_core_fc_last::thread_or_ln74_125_fu_7158_p2() {
    or_ln74_125_fu_7158_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_7E);
}

void snn_core_fc_last::thread_or_ln74_126_fu_7172_p2() {
    or_ln74_126_fu_7172_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_7F);
}

void snn_core_fc_last::thread_or_ln74_127_fu_7186_p2() {
    or_ln74_127_fu_7186_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_80);
}

void snn_core_fc_last::thread_or_ln74_128_fu_7200_p2() {
    or_ln74_128_fu_7200_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_81);
}

void snn_core_fc_last::thread_or_ln74_129_fu_7214_p2() {
    or_ln74_129_fu_7214_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_82);
}

void snn_core_fc_last::thread_or_ln74_12_fu_5576_p2() {
    or_ln74_12_fu_5576_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_D);
}

void snn_core_fc_last::thread_or_ln74_130_fu_7228_p2() {
    or_ln74_130_fu_7228_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_83);
}

void snn_core_fc_last::thread_or_ln74_131_fu_7242_p2() {
    or_ln74_131_fu_7242_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_84);
}

void snn_core_fc_last::thread_or_ln74_132_fu_7256_p2() {
    or_ln74_132_fu_7256_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_85);
}

void snn_core_fc_last::thread_or_ln74_133_fu_7270_p2() {
    or_ln74_133_fu_7270_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_86);
}

void snn_core_fc_last::thread_or_ln74_134_fu_7284_p2() {
    or_ln74_134_fu_7284_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_87);
}

void snn_core_fc_last::thread_or_ln74_135_fu_7298_p2() {
    or_ln74_135_fu_7298_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_88);
}

void snn_core_fc_last::thread_or_ln74_136_fu_7312_p2() {
    or_ln74_136_fu_7312_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_89);
}

void snn_core_fc_last::thread_or_ln74_137_fu_7326_p2() {
    or_ln74_137_fu_7326_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_8A);
}

void snn_core_fc_last::thread_or_ln74_138_fu_7340_p2() {
    or_ln74_138_fu_7340_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_8B);
}

void snn_core_fc_last::thread_or_ln74_139_fu_7354_p2() {
    or_ln74_139_fu_7354_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_8C);
}

void snn_core_fc_last::thread_or_ln74_13_fu_5590_p2() {
    or_ln74_13_fu_5590_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_E);
}

void snn_core_fc_last::thread_or_ln74_140_fu_7368_p2() {
    or_ln74_140_fu_7368_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_8D);
}

void snn_core_fc_last::thread_or_ln74_141_fu_7382_p2() {
    or_ln74_141_fu_7382_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_8E);
}

void snn_core_fc_last::thread_or_ln74_142_fu_7396_p2() {
    or_ln74_142_fu_7396_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_8F);
}

void snn_core_fc_last::thread_or_ln74_143_fu_7410_p2() {
    or_ln74_143_fu_7410_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_90);
}

void snn_core_fc_last::thread_or_ln74_144_fu_7424_p2() {
    or_ln74_144_fu_7424_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_91);
}

void snn_core_fc_last::thread_or_ln74_145_fu_7438_p2() {
    or_ln74_145_fu_7438_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_92);
}

void snn_core_fc_last::thread_or_ln74_146_fu_7452_p2() {
    or_ln74_146_fu_7452_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_93);
}

void snn_core_fc_last::thread_or_ln74_147_fu_7466_p2() {
    or_ln74_147_fu_7466_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_94);
}

void snn_core_fc_last::thread_or_ln74_148_fu_7480_p2() {
    or_ln74_148_fu_7480_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_95);
}

void snn_core_fc_last::thread_or_ln74_149_fu_7494_p2() {
    or_ln74_149_fu_7494_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_96);
}

void snn_core_fc_last::thread_or_ln74_14_fu_5604_p2() {
    or_ln74_14_fu_5604_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_F);
}

void snn_core_fc_last::thread_or_ln74_150_fu_7508_p2() {
    or_ln74_150_fu_7508_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_97);
}

void snn_core_fc_last::thread_or_ln74_151_fu_7522_p2() {
    or_ln74_151_fu_7522_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_98);
}

void snn_core_fc_last::thread_or_ln74_152_fu_7536_p2() {
    or_ln74_152_fu_7536_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_99);
}

void snn_core_fc_last::thread_or_ln74_153_fu_7550_p2() {
    or_ln74_153_fu_7550_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_9A);
}

void snn_core_fc_last::thread_or_ln74_154_fu_7564_p2() {
    or_ln74_154_fu_7564_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_9B);
}

void snn_core_fc_last::thread_or_ln74_155_fu_7578_p2() {
    or_ln74_155_fu_7578_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_9C);
}

void snn_core_fc_last::thread_or_ln74_156_fu_7592_p2() {
    or_ln74_156_fu_7592_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_9D);
}

void snn_core_fc_last::thread_or_ln74_157_fu_7606_p2() {
    or_ln74_157_fu_7606_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_9E);
}

void snn_core_fc_last::thread_or_ln74_158_fu_7620_p2() {
    or_ln74_158_fu_7620_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_9F);
}

void snn_core_fc_last::thread_or_ln74_159_fu_7634_p2() {
    or_ln74_159_fu_7634_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_A0);
}

void snn_core_fc_last::thread_or_ln74_15_fu_5618_p2() {
    or_ln74_15_fu_5618_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_10);
}

void snn_core_fc_last::thread_or_ln74_160_fu_7648_p2() {
    or_ln74_160_fu_7648_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_A1);
}

void snn_core_fc_last::thread_or_ln74_161_fu_7662_p2() {
    or_ln74_161_fu_7662_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_A2);
}

void snn_core_fc_last::thread_or_ln74_162_fu_7676_p2() {
    or_ln74_162_fu_7676_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_A3);
}

void snn_core_fc_last::thread_or_ln74_163_fu_7690_p2() {
    or_ln74_163_fu_7690_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_A4);
}

void snn_core_fc_last::thread_or_ln74_164_fu_7704_p2() {
    or_ln74_164_fu_7704_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_A5);
}

void snn_core_fc_last::thread_or_ln74_165_fu_7718_p2() {
    or_ln74_165_fu_7718_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_A6);
}

void snn_core_fc_last::thread_or_ln74_166_fu_7732_p2() {
    or_ln74_166_fu_7732_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_A7);
}

void snn_core_fc_last::thread_or_ln74_167_fu_7746_p2() {
    or_ln74_167_fu_7746_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_A8);
}

void snn_core_fc_last::thread_or_ln74_168_fu_7760_p2() {
    or_ln74_168_fu_7760_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_A9);
}

void snn_core_fc_last::thread_or_ln74_169_fu_7774_p2() {
    or_ln74_169_fu_7774_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_AA);
}

void snn_core_fc_last::thread_or_ln74_16_fu_5632_p2() {
    or_ln74_16_fu_5632_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_11);
}

void snn_core_fc_last::thread_or_ln74_170_fu_7788_p2() {
    or_ln74_170_fu_7788_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_AB);
}

void snn_core_fc_last::thread_or_ln74_171_fu_7802_p2() {
    or_ln74_171_fu_7802_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_AC);
}

void snn_core_fc_last::thread_or_ln74_172_fu_7816_p2() {
    or_ln74_172_fu_7816_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_AD);
}

void snn_core_fc_last::thread_or_ln74_173_fu_7830_p2() {
    or_ln74_173_fu_7830_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_AE);
}

void snn_core_fc_last::thread_or_ln74_174_fu_7844_p2() {
    or_ln74_174_fu_7844_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_AF);
}

void snn_core_fc_last::thread_or_ln74_175_fu_7858_p2() {
    or_ln74_175_fu_7858_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_B0);
}

void snn_core_fc_last::thread_or_ln74_176_fu_7872_p2() {
    or_ln74_176_fu_7872_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_B1);
}

void snn_core_fc_last::thread_or_ln74_177_fu_7886_p2() {
    or_ln74_177_fu_7886_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_B2);
}

void snn_core_fc_last::thread_or_ln74_178_fu_7900_p2() {
    or_ln74_178_fu_7900_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_B3);
}

void snn_core_fc_last::thread_or_ln74_179_fu_7914_p2() {
    or_ln74_179_fu_7914_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_B4);
}

void snn_core_fc_last::thread_or_ln74_17_fu_5646_p2() {
    or_ln74_17_fu_5646_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_12);
}

void snn_core_fc_last::thread_or_ln74_180_fu_7928_p2() {
    or_ln74_180_fu_7928_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_B5);
}

void snn_core_fc_last::thread_or_ln74_181_fu_7942_p2() {
    or_ln74_181_fu_7942_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_B6);
}

void snn_core_fc_last::thread_or_ln74_182_fu_7956_p2() {
    or_ln74_182_fu_7956_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_B7);
}

void snn_core_fc_last::thread_or_ln74_183_fu_7970_p2() {
    or_ln74_183_fu_7970_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_B8);
}

void snn_core_fc_last::thread_or_ln74_184_fu_7984_p2() {
    or_ln74_184_fu_7984_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_B9);
}

void snn_core_fc_last::thread_or_ln74_185_fu_7998_p2() {
    or_ln74_185_fu_7998_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_BA);
}

void snn_core_fc_last::thread_or_ln74_186_fu_8012_p2() {
    or_ln74_186_fu_8012_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_BB);
}

void snn_core_fc_last::thread_or_ln74_187_fu_8026_p2() {
    or_ln74_187_fu_8026_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_BC);
}

void snn_core_fc_last::thread_or_ln74_188_fu_8040_p2() {
    or_ln74_188_fu_8040_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_BD);
}

void snn_core_fc_last::thread_or_ln74_189_fu_8054_p2() {
    or_ln74_189_fu_8054_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_BE);
}

void snn_core_fc_last::thread_or_ln74_18_fu_5660_p2() {
    or_ln74_18_fu_5660_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_13);
}

void snn_core_fc_last::thread_or_ln74_190_fu_8068_p2() {
    or_ln74_190_fu_8068_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_BF);
}

void snn_core_fc_last::thread_or_ln74_191_fu_8082_p2() {
    or_ln74_191_fu_8082_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_C0);
}

void snn_core_fc_last::thread_or_ln74_192_fu_8096_p2() {
    or_ln74_192_fu_8096_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_C1);
}

void snn_core_fc_last::thread_or_ln74_193_fu_8110_p2() {
    or_ln74_193_fu_8110_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_C2);
}

void snn_core_fc_last::thread_or_ln74_194_fu_8124_p2() {
    or_ln74_194_fu_8124_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_C3);
}

void snn_core_fc_last::thread_or_ln74_195_fu_8138_p2() {
    or_ln74_195_fu_8138_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_C4);
}

void snn_core_fc_last::thread_or_ln74_196_fu_8152_p2() {
    or_ln74_196_fu_8152_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_C5);
}

void snn_core_fc_last::thread_or_ln74_197_fu_8166_p2() {
    or_ln74_197_fu_8166_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_C6);
}

void snn_core_fc_last::thread_or_ln74_198_fu_8180_p2() {
    or_ln74_198_fu_8180_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_C7);
}

void snn_core_fc_last::thread_or_ln74_199_fu_8194_p2() {
    or_ln74_199_fu_8194_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_C8);
}

void snn_core_fc_last::thread_or_ln74_19_fu_5674_p2() {
    or_ln74_19_fu_5674_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_14);
}

void snn_core_fc_last::thread_or_ln74_1_fu_5422_p2() {
    or_ln74_1_fu_5422_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_2);
}

void snn_core_fc_last::thread_or_ln74_200_fu_8208_p2() {
    or_ln74_200_fu_8208_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_C9);
}

void snn_core_fc_last::thread_or_ln74_201_fu_8222_p2() {
    or_ln74_201_fu_8222_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_CA);
}

void snn_core_fc_last::thread_or_ln74_202_fu_8236_p2() {
    or_ln74_202_fu_8236_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_CB);
}

void snn_core_fc_last::thread_or_ln74_203_fu_8250_p2() {
    or_ln74_203_fu_8250_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_CC);
}

void snn_core_fc_last::thread_or_ln74_204_fu_8264_p2() {
    or_ln74_204_fu_8264_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_CD);
}

void snn_core_fc_last::thread_or_ln74_205_fu_8278_p2() {
    or_ln74_205_fu_8278_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_CE);
}

void snn_core_fc_last::thread_or_ln74_206_fu_8292_p2() {
    or_ln74_206_fu_8292_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_CF);
}

void snn_core_fc_last::thread_or_ln74_207_fu_8306_p2() {
    or_ln74_207_fu_8306_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_D0);
}

void snn_core_fc_last::thread_or_ln74_208_fu_8320_p2() {
    or_ln74_208_fu_8320_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_D1);
}

void snn_core_fc_last::thread_or_ln74_209_fu_8334_p2() {
    or_ln74_209_fu_8334_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_D2);
}

void snn_core_fc_last::thread_or_ln74_20_fu_5688_p2() {
    or_ln74_20_fu_5688_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_15);
}

void snn_core_fc_last::thread_or_ln74_210_fu_8348_p2() {
    or_ln74_210_fu_8348_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_D3);
}

void snn_core_fc_last::thread_or_ln74_211_fu_8362_p2() {
    or_ln74_211_fu_8362_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_D4);
}

void snn_core_fc_last::thread_or_ln74_212_fu_8376_p2() {
    or_ln74_212_fu_8376_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_D5);
}

void snn_core_fc_last::thread_or_ln74_213_fu_8390_p2() {
    or_ln74_213_fu_8390_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_D6);
}

void snn_core_fc_last::thread_or_ln74_214_fu_8404_p2() {
    or_ln74_214_fu_8404_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_D7);
}

void snn_core_fc_last::thread_or_ln74_215_fu_8418_p2() {
    or_ln74_215_fu_8418_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_D8);
}

void snn_core_fc_last::thread_or_ln74_216_fu_8432_p2() {
    or_ln74_216_fu_8432_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_D9);
}

void snn_core_fc_last::thread_or_ln74_217_fu_8446_p2() {
    or_ln74_217_fu_8446_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_DA);
}

void snn_core_fc_last::thread_or_ln74_218_fu_8460_p2() {
    or_ln74_218_fu_8460_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_DB);
}

void snn_core_fc_last::thread_or_ln74_219_fu_8474_p2() {
    or_ln74_219_fu_8474_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_DC);
}

void snn_core_fc_last::thread_or_ln74_21_fu_5702_p2() {
    or_ln74_21_fu_5702_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_16);
}

void snn_core_fc_last::thread_or_ln74_220_fu_8488_p2() {
    or_ln74_220_fu_8488_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_DD);
}

void snn_core_fc_last::thread_or_ln74_221_fu_8502_p2() {
    or_ln74_221_fu_8502_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_DE);
}

void snn_core_fc_last::thread_or_ln74_222_fu_8516_p2() {
    or_ln74_222_fu_8516_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_DF);
}

void snn_core_fc_last::thread_or_ln74_223_fu_8530_p2() {
    or_ln74_223_fu_8530_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_E0);
}

void snn_core_fc_last::thread_or_ln74_224_fu_8544_p2() {
    or_ln74_224_fu_8544_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_E1);
}

void snn_core_fc_last::thread_or_ln74_225_fu_8558_p2() {
    or_ln74_225_fu_8558_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_E2);
}

void snn_core_fc_last::thread_or_ln74_226_fu_8572_p2() {
    or_ln74_226_fu_8572_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_E3);
}

void snn_core_fc_last::thread_or_ln74_227_fu_8586_p2() {
    or_ln74_227_fu_8586_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_E4);
}

void snn_core_fc_last::thread_or_ln74_228_fu_8600_p2() {
    or_ln74_228_fu_8600_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_E5);
}

void snn_core_fc_last::thread_or_ln74_229_fu_8614_p2() {
    or_ln74_229_fu_8614_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_E6);
}

void snn_core_fc_last::thread_or_ln74_22_fu_5716_p2() {
    or_ln74_22_fu_5716_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_17);
}

void snn_core_fc_last::thread_or_ln74_230_fu_8628_p2() {
    or_ln74_230_fu_8628_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_E7);
}

void snn_core_fc_last::thread_or_ln74_231_fu_8642_p2() {
    or_ln74_231_fu_8642_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_E8);
}

void snn_core_fc_last::thread_or_ln74_232_fu_8656_p2() {
    or_ln74_232_fu_8656_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_E9);
}

void snn_core_fc_last::thread_or_ln74_233_fu_8670_p2() {
    or_ln74_233_fu_8670_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_EA);
}

void snn_core_fc_last::thread_or_ln74_234_fu_8684_p2() {
    or_ln74_234_fu_8684_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_EB);
}

void snn_core_fc_last::thread_or_ln74_235_fu_8698_p2() {
    or_ln74_235_fu_8698_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_EC);
}

void snn_core_fc_last::thread_or_ln74_236_fu_8712_p2() {
    or_ln74_236_fu_8712_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_ED);
}

void snn_core_fc_last::thread_or_ln74_237_fu_8726_p2() {
    or_ln74_237_fu_8726_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_EE);
}

void snn_core_fc_last::thread_or_ln74_238_fu_8740_p2() {
    or_ln74_238_fu_8740_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_EF);
}

void snn_core_fc_last::thread_or_ln74_239_fu_8754_p2() {
    or_ln74_239_fu_8754_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_F0);
}

void snn_core_fc_last::thread_or_ln74_23_fu_5730_p2() {
    or_ln74_23_fu_5730_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_18);
}

void snn_core_fc_last::thread_or_ln74_240_fu_8768_p2() {
    or_ln74_240_fu_8768_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_F1);
}

void snn_core_fc_last::thread_or_ln74_241_fu_8782_p2() {
    or_ln74_241_fu_8782_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_F2);
}

void snn_core_fc_last::thread_or_ln74_242_fu_8796_p2() {
    or_ln74_242_fu_8796_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_F3);
}

void snn_core_fc_last::thread_or_ln74_243_fu_8810_p2() {
    or_ln74_243_fu_8810_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_F4);
}

void snn_core_fc_last::thread_or_ln74_244_fu_8824_p2() {
    or_ln74_244_fu_8824_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_F5);
}

void snn_core_fc_last::thread_or_ln74_245_fu_8838_p2() {
    or_ln74_245_fu_8838_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_F6);
}

void snn_core_fc_last::thread_or_ln74_246_fu_8852_p2() {
    or_ln74_246_fu_8852_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_F7);
}

void snn_core_fc_last::thread_or_ln74_247_fu_8866_p2() {
    or_ln74_247_fu_8866_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_F8);
}

void snn_core_fc_last::thread_or_ln74_248_fu_8880_p2() {
    or_ln74_248_fu_8880_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_F9);
}

void snn_core_fc_last::thread_or_ln74_249_fu_8894_p2() {
    or_ln74_249_fu_8894_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_FA);
}

void snn_core_fc_last::thread_or_ln74_24_fu_5744_p2() {
    or_ln74_24_fu_5744_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_19);
}

void snn_core_fc_last::thread_or_ln74_250_fu_8908_p2() {
    or_ln74_250_fu_8908_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_FB);
}

void snn_core_fc_last::thread_or_ln74_251_fu_8922_p2() {
    or_ln74_251_fu_8922_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_FC);
}

void snn_core_fc_last::thread_or_ln74_252_fu_8936_p2() {
    or_ln74_252_fu_8936_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_FD);
}

void snn_core_fc_last::thread_or_ln74_253_fu_8950_p2() {
    or_ln74_253_fu_8950_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_FE);
}

void snn_core_fc_last::thread_or_ln74_254_fu_8964_p2() {
    or_ln74_254_fu_8964_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_FF);
}

void snn_core_fc_last::thread_or_ln74_25_fu_5758_p2() {
    or_ln74_25_fu_5758_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_1A);
}

void snn_core_fc_last::thread_or_ln74_26_fu_5772_p2() {
    or_ln74_26_fu_5772_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_1B);
}

void snn_core_fc_last::thread_or_ln74_27_fu_5786_p2() {
    or_ln74_27_fu_5786_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_1C);
}

void snn_core_fc_last::thread_or_ln74_28_fu_5800_p2() {
    or_ln74_28_fu_5800_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_1D);
}

void snn_core_fc_last::thread_or_ln74_29_fu_5814_p2() {
    or_ln74_29_fu_5814_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_1E);
}

void snn_core_fc_last::thread_or_ln74_2_fu_5436_p2() {
    or_ln74_2_fu_5436_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_3);
}

void snn_core_fc_last::thread_or_ln74_30_fu_5828_p2() {
    or_ln74_30_fu_5828_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_1F);
}

void snn_core_fc_last::thread_or_ln74_31_fu_5842_p2() {
    or_ln74_31_fu_5842_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_20);
}

void snn_core_fc_last::thread_or_ln74_32_fu_5856_p2() {
    or_ln74_32_fu_5856_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_21);
}

void snn_core_fc_last::thread_or_ln74_33_fu_5870_p2() {
    or_ln74_33_fu_5870_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_22);
}

void snn_core_fc_last::thread_or_ln74_34_fu_5884_p2() {
    or_ln74_34_fu_5884_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_23);
}

void snn_core_fc_last::thread_or_ln74_35_fu_5898_p2() {
    or_ln74_35_fu_5898_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_24);
}

void snn_core_fc_last::thread_or_ln74_36_fu_5912_p2() {
    or_ln74_36_fu_5912_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_25);
}

void snn_core_fc_last::thread_or_ln74_37_fu_5926_p2() {
    or_ln74_37_fu_5926_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_26);
}

void snn_core_fc_last::thread_or_ln74_38_fu_5940_p2() {
    or_ln74_38_fu_5940_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_27);
}

void snn_core_fc_last::thread_or_ln74_39_fu_5954_p2() {
    or_ln74_39_fu_5954_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_28);
}

void snn_core_fc_last::thread_or_ln74_3_fu_5450_p2() {
    or_ln74_3_fu_5450_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_4);
}

void snn_core_fc_last::thread_or_ln74_40_fu_5968_p2() {
    or_ln74_40_fu_5968_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_29);
}

void snn_core_fc_last::thread_or_ln74_41_fu_5982_p2() {
    or_ln74_41_fu_5982_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_2A);
}

void snn_core_fc_last::thread_or_ln74_42_fu_5996_p2() {
    or_ln74_42_fu_5996_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_2B);
}

void snn_core_fc_last::thread_or_ln74_43_fu_6010_p2() {
    or_ln74_43_fu_6010_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_2C);
}

void snn_core_fc_last::thread_or_ln74_44_fu_6024_p2() {
    or_ln74_44_fu_6024_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_2D);
}

void snn_core_fc_last::thread_or_ln74_45_fu_6038_p2() {
    or_ln74_45_fu_6038_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_2E);
}

void snn_core_fc_last::thread_or_ln74_46_fu_6052_p2() {
    or_ln74_46_fu_6052_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_2F);
}

void snn_core_fc_last::thread_or_ln74_47_fu_6066_p2() {
    or_ln74_47_fu_6066_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_30);
}

void snn_core_fc_last::thread_or_ln74_48_fu_6080_p2() {
    or_ln74_48_fu_6080_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_31);
}

void snn_core_fc_last::thread_or_ln74_49_fu_6094_p2() {
    or_ln74_49_fu_6094_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_32);
}

void snn_core_fc_last::thread_or_ln74_4_fu_5464_p2() {
    or_ln74_4_fu_5464_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_5);
}

void snn_core_fc_last::thread_or_ln74_50_fu_6108_p2() {
    or_ln74_50_fu_6108_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_33);
}

void snn_core_fc_last::thread_or_ln74_51_fu_6122_p2() {
    or_ln74_51_fu_6122_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_34);
}

void snn_core_fc_last::thread_or_ln74_52_fu_6136_p2() {
    or_ln74_52_fu_6136_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_35);
}

void snn_core_fc_last::thread_or_ln74_53_fu_6150_p2() {
    or_ln74_53_fu_6150_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_36);
}

void snn_core_fc_last::thread_or_ln74_54_fu_6164_p2() {
    or_ln74_54_fu_6164_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_37);
}

void snn_core_fc_last::thread_or_ln74_55_fu_6178_p2() {
    or_ln74_55_fu_6178_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_38);
}

void snn_core_fc_last::thread_or_ln74_56_fu_6192_p2() {
    or_ln74_56_fu_6192_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_39);
}

void snn_core_fc_last::thread_or_ln74_57_fu_6206_p2() {
    or_ln74_57_fu_6206_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_3A);
}

void snn_core_fc_last::thread_or_ln74_58_fu_6220_p2() {
    or_ln74_58_fu_6220_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_3B);
}

void snn_core_fc_last::thread_or_ln74_59_fu_6234_p2() {
    or_ln74_59_fu_6234_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_3C);
}

void snn_core_fc_last::thread_or_ln74_5_fu_5478_p2() {
    or_ln74_5_fu_5478_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_6);
}

void snn_core_fc_last::thread_or_ln74_60_fu_6248_p2() {
    or_ln74_60_fu_6248_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_3D);
}

void snn_core_fc_last::thread_or_ln74_61_fu_6262_p2() {
    or_ln74_61_fu_6262_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_3E);
}

void snn_core_fc_last::thread_or_ln74_62_fu_6276_p2() {
    or_ln74_62_fu_6276_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_3F);
}

void snn_core_fc_last::thread_or_ln74_63_fu_6290_p2() {
    or_ln74_63_fu_6290_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_40);
}

void snn_core_fc_last::thread_or_ln74_64_fu_6304_p2() {
    or_ln74_64_fu_6304_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_41);
}

void snn_core_fc_last::thread_or_ln74_65_fu_6318_p2() {
    or_ln74_65_fu_6318_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_42);
}

void snn_core_fc_last::thread_or_ln74_66_fu_6332_p2() {
    or_ln74_66_fu_6332_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_43);
}

void snn_core_fc_last::thread_or_ln74_67_fu_6346_p2() {
    or_ln74_67_fu_6346_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_44);
}

void snn_core_fc_last::thread_or_ln74_68_fu_6360_p2() {
    or_ln74_68_fu_6360_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_45);
}

void snn_core_fc_last::thread_or_ln74_69_fu_6374_p2() {
    or_ln74_69_fu_6374_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_46);
}

void snn_core_fc_last::thread_or_ln74_6_fu_5492_p2() {
    or_ln74_6_fu_5492_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_7);
}

void snn_core_fc_last::thread_or_ln74_70_fu_6388_p2() {
    or_ln74_70_fu_6388_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_47);
}

void snn_core_fc_last::thread_or_ln74_71_fu_6402_p2() {
    or_ln74_71_fu_6402_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_48);
}

void snn_core_fc_last::thread_or_ln74_72_fu_6416_p2() {
    or_ln74_72_fu_6416_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_49);
}

void snn_core_fc_last::thread_or_ln74_73_fu_6430_p2() {
    or_ln74_73_fu_6430_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_4A);
}

void snn_core_fc_last::thread_or_ln74_74_fu_6444_p2() {
    or_ln74_74_fu_6444_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_4B);
}

void snn_core_fc_last::thread_or_ln74_75_fu_6458_p2() {
    or_ln74_75_fu_6458_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_4C);
}

void snn_core_fc_last::thread_or_ln74_76_fu_6472_p2() {
    or_ln74_76_fu_6472_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_4D);
}

void snn_core_fc_last::thread_or_ln74_77_fu_6486_p2() {
    or_ln74_77_fu_6486_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_4E);
}

void snn_core_fc_last::thread_or_ln74_78_fu_6500_p2() {
    or_ln74_78_fu_6500_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_4F);
}

void snn_core_fc_last::thread_or_ln74_79_fu_6514_p2() {
    or_ln74_79_fu_6514_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_50);
}

void snn_core_fc_last::thread_or_ln74_7_fu_5506_p2() {
    or_ln74_7_fu_5506_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_8);
}

void snn_core_fc_last::thread_or_ln74_80_fu_6528_p2() {
    or_ln74_80_fu_6528_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_51);
}

void snn_core_fc_last::thread_or_ln74_81_fu_6542_p2() {
    or_ln74_81_fu_6542_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_52);
}

void snn_core_fc_last::thread_or_ln74_82_fu_6556_p2() {
    or_ln74_82_fu_6556_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_53);
}

void snn_core_fc_last::thread_or_ln74_83_fu_6570_p2() {
    or_ln74_83_fu_6570_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_54);
}

void snn_core_fc_last::thread_or_ln74_84_fu_6584_p2() {
    or_ln74_84_fu_6584_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_55);
}

void snn_core_fc_last::thread_or_ln74_85_fu_6598_p2() {
    or_ln74_85_fu_6598_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_56);
}

void snn_core_fc_last::thread_or_ln74_86_fu_6612_p2() {
    or_ln74_86_fu_6612_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_57);
}

void snn_core_fc_last::thread_or_ln74_87_fu_6626_p2() {
    or_ln74_87_fu_6626_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_58);
}

void snn_core_fc_last::thread_or_ln74_88_fu_6640_p2() {
    or_ln74_88_fu_6640_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_59);
}

void snn_core_fc_last::thread_or_ln74_89_fu_6654_p2() {
    or_ln74_89_fu_6654_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_5A);
}

void snn_core_fc_last::thread_or_ln74_8_fu_5520_p2() {
    or_ln74_8_fu_5520_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_9);
}

void snn_core_fc_last::thread_or_ln74_90_fu_6668_p2() {
    or_ln74_90_fu_6668_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_5B);
}

void snn_core_fc_last::thread_or_ln74_91_fu_6682_p2() {
    or_ln74_91_fu_6682_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_5C);
}

void snn_core_fc_last::thread_or_ln74_92_fu_6696_p2() {
    or_ln74_92_fu_6696_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_5D);
}

void snn_core_fc_last::thread_or_ln74_93_fu_6710_p2() {
    or_ln74_93_fu_6710_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_5E);
}

void snn_core_fc_last::thread_or_ln74_94_fu_6724_p2() {
    or_ln74_94_fu_6724_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_5F);
}

void snn_core_fc_last::thread_or_ln74_95_fu_6738_p2() {
    or_ln74_95_fu_6738_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_60);
}

void snn_core_fc_last::thread_or_ln74_96_fu_6752_p2() {
    or_ln74_96_fu_6752_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_61);
}

void snn_core_fc_last::thread_or_ln74_97_fu_6766_p2() {
    or_ln74_97_fu_6766_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_62);
}

void snn_core_fc_last::thread_or_ln74_98_fu_6780_p2() {
    or_ln74_98_fu_6780_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_63);
}

void snn_core_fc_last::thread_or_ln74_99_fu_6794_p2() {
    or_ln74_99_fu_6794_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_64);
}

void snn_core_fc_last::thread_or_ln74_9_fu_5534_p2() {
    or_ln74_9_fu_5534_p2 = (tmp_13_reg_11751.read() | ap_const_lv12_A);
}

void snn_core_fc_last::thread_or_ln74_fu_5407_p2() {
    or_ln74_fu_5407_p2 = (tmp_13_fu_5394_p3.read() | ap_const_lv12_1);
}

void snn_core_fc_last::thread_or_ln90_1_fu_9121_p2() {
    or_ln90_1_fu_9121_p2 = (icmp_ln90_3_reg_14615.read() | icmp_ln90_2_reg_14610.read());
}

void snn_core_fc_last::thread_or_ln90_fu_9117_p2() {
    or_ln90_fu_9117_p2 = (icmp_ln90_1_reg_14605.read() | icmp_ln90_reg_14600.read());
}

void snn_core_fc_last::thread_out_spike_fu_9028_p3() {
    out_spike_fu_9028_p3 = (!and_ln16_reg_14569.read()[0].is_01())? sc_lv<32>(): ((and_ln16_reg_14569.read()[0].to_bool())? ap_const_lv32_3F800000: ap_const_lv32_0);
}

void snn_core_fc_last::thread_select_ln16_fu_9020_p3() {
    select_ln16_fu_9020_p3 = (!and_ln16_reg_14569.read()[0].is_01())? sc_lv<32>(): ((and_ln16_reg_14569.read()[0].to_bool())? ap_const_lv32_0: reg_5300.read());
}

void snn_core_fc_last::thread_spike_count_address0() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_pp3_stage0.read()) && 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_enable_reg_pp3_iter0.read()) && 
         esl_seteq<1,1,1>(ap_block_pp3_stage0.read(), ap_const_boolean_0))) {
        spike_count_address0 =  (sc_lv<4>) (zext_ln90_fu_9042_p1.read());
    } else if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_pp2_stage18.read()) && 
                esl_seteq<1,1,1>(ap_const_logic_1, ap_enable_reg_pp2_iter10.read()) && 
                esl_seteq<1,1,1>(ap_block_pp2_stage18.read(), ap_const_boolean_0))) {
        spike_count_address0 = spike_count_addr_3_reg_12024_pp2_iter10_reg.read();
    } else if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_pp2_stage0.read()) && 
                esl_seteq<1,1,1>(ap_const_logic_1, ap_enable_reg_pp2_iter10.read()) && 
                esl_seteq<1,1,1>(ap_block_pp2_stage0.read(), ap_const_boolean_0))) {
        spike_count_address0 = spike_count_addr_3_reg_12024_pp2_iter9_reg.read();
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state4.read())) {
        spike_count_address0 =  (sc_lv<4>) (ap_const_lv64_0);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        spike_count_address0 =  (sc_lv<4>) (zext_ln44_fu_5318_p1.read());
    } else {
        spike_count_address0 =  (sc_lv<4>) ("XXXX");
    }
}

void snn_core_fc_last::thread_spike_count_ce0() {
    if (((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_pp2_stage0.read()) && 
          esl_seteq<1,1,1>(ap_block_pp2_stage0_11001.read(), ap_const_boolean_0) && 
          esl_seteq<1,1,1>(ap_const_logic_1, ap_enable_reg_pp2_iter10.read())) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state4.read()) || 
         (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_pp3_stage0.read()) && 
          esl_seteq<1,1,1>(ap_block_pp3_stage0_11001.read(), ap_const_boolean_0) && 
          esl_seteq<1,1,1>(ap_const_logic_1, ap_enable_reg_pp3_iter0.read())) || 
         (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_pp2_stage18.read()) && 
          esl_seteq<1,1,1>(ap_block_pp2_stage18_11001.read(), ap_const_boolean_0) && 
          esl_seteq<1,1,1>(ap_const_logic_1, ap_enable_reg_pp2_iter10.read())))) {
        spike_count_ce0 = ap_const_logic_1;
    } else {
        spike_count_ce0 = ap_const_logic_0;
    }
}

void snn_core_fc_last::thread_spike_count_d0() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_pp2_stage18.read()) && 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_enable_reg_pp2_iter10.read()) && 
         esl_seteq<1,1,1>(ap_block_pp2_stage18.read(), ap_const_boolean_0))) {
        spike_count_d0 = reg_5300.read();
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        spike_count_d0 = ap_const_lv32_0;
    } else {
        spike_count_d0 =  (sc_lv<32>) ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    }
}

void snn_core_fc_last::thread_spike_count_we0() {
    if (((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
          esl_seteq<1,1,1>(ap_const_lv1_0, icmp_ln42_fu_5306_p2.read())) || 
         (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_pp2_stage18.read()) && 
          esl_seteq<1,1,1>(ap_block_pp2_stage18_11001.read(), ap_const_boolean_0) && 
          esl_seteq<1,1,1>(ap_const_logic_1, ap_enable_reg_pp2_iter10.read()) && 
          esl_seteq<1,1,1>(ap_const_lv1_0, icmp_ln67_reg_11742_pp2_iter10_reg.read())))) {
        spike_count_we0 = ap_const_logic_1;
    } else {
        spike_count_we0 = ap_const_logic_0;
    }
}

void snn_core_fc_last::thread_spike_in_address0() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state133.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_FF);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state132.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_FD);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state131.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_FB);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state130.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_F9);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state129.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_F7);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state128.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_F5);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state127.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_F3);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state126.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_F1);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state125.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_EF);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state124.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_ED);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state123.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_EB);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state122.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_E9);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state121.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_E7);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state120.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_E5);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state119.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_E3);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state118.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_E1);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state117.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_DF);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state116.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_DD);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state115.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_DB);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state114.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_D9);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state113.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_D7);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state112.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_D5);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state111.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_D3);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state110.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_D1);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state109.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_CF);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state108.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_CD);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state107.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_CB);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state106.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_C9);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state105.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_C7);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state104.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_C5);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state103.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_C3);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state102.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_C1);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state101.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_BF);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state100.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_BD);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state99.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_BB);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state98.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_B9);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state97.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_B7);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state96.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_B5);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state95.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_B3);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state94.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_B1);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state93.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_AF);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state92.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_AD);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state91.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_AB);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state90.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_A9);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state89.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_A7);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state88.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_A5);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state87.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_A3);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state86.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_A1);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state85.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_9F);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state84.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_9D);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state83.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_9B);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state82.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_99);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state81.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_97);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state80.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_95);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state79.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_93);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state78.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_91);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state77.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_8F);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state76.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_8D);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state75.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_8B);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state74.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_89);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state73.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_87);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state72.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_85);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state71.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_83);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state70.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_81);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state69.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_7F);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state68.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_7D);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state67.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_7B);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state66.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_79);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state65.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_77);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state64.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_75);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state63.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_73);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state62.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_71);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state61.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_6F);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state60.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_6D);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state59.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_6B);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state58.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_69);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state57.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_67);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state56.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_65);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state55.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_63);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state54.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_61);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state53.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_5F);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state52.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_5D);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state51.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_5B);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state50.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_59);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state49.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_57);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state48.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_55);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state47.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_53);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state46.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_51);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state45.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_4F);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state44.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_4D);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state43.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_4B);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state42.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_49);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state41.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_47);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state40.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_45);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state39.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_43);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state38.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_41);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state37.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_3F);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state36.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_3D);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state35.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_3B);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state34.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_39);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state33.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_37);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state32.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_35);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state31.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_33);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state30.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_31);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state29.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_2F);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state28.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_2D);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state27.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_2B);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state26.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_29);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state25.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_27);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state24.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_25);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state23.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_23);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state22.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_21);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state21.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_1F);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state20.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_1D);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state19.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_1B);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state18.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_19);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state17.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_17);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state16.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_15);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state15.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_13);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state14.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_11);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state13.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_F);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state12.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_D);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state11.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_B);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state10.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_9);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state9.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_7);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state8.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_5);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state7.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_3);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state6.read())) {
        spike_in_address0 =  (sc_lv<8>) (ap_const_lv64_0);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state5.read())) {
        spike_in_address0 =  (sc_lv<8>) (zext_ln62_fu_5371_p1.read());
    } else {
        spike_in_address0 =  (sc_lv<8>) ("XXXXXXXX");
    }
}

void snn_core_fc_last::thread_spike_in_address1() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state133.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_FE);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state132.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_FC);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state131.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_FA);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state130.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_F8);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state129.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_F6);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state128.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_F4);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state127.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_F2);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state126.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_F0);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state125.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_EE);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state124.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_EC);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state123.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_EA);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state122.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_E8);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state121.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_E6);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state120.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_E4);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state119.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_E2);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state118.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_E0);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state117.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_DE);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state116.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_DC);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state115.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_DA);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state114.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_D8);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state113.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_D6);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state112.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_D4);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state111.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_D2);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state110.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_D0);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state109.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_CE);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state108.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_CC);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state107.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_CA);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state106.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_C8);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state105.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_C6);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state104.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_C4);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state103.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_C2);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state102.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_C0);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state101.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_BE);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state100.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_BC);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state99.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_BA);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state98.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_B8);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state97.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_B6);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state96.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_B4);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state95.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_B2);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state94.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_B0);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state93.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_AE);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state92.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_AC);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state91.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_AA);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state90.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_A8);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state89.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_A6);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state88.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_A4);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state87.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_A2);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state86.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_A0);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state85.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_9E);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state84.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_9C);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state83.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_9A);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state82.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_98);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state81.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_96);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state80.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_94);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state79.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_92);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state78.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_90);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state77.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_8E);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state76.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_8C);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state75.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_8A);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state74.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_88);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state73.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_86);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state72.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_84);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state71.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_82);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state70.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_80);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state69.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_7E);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state68.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_7C);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state67.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_7A);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state66.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_78);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state65.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_76);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state64.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_74);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state63.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_72);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state62.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_70);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state61.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_6E);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state60.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_6C);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state59.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_6A);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state58.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_68);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state57.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_66);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state56.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_64);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state55.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_62);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state54.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_60);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state53.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_5E);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state52.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_5C);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state51.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_5A);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state50.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_58);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state49.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_56);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state48.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_54);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state47.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_52);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state46.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_50);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state45.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_4E);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state44.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_4C);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state43.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_4A);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state42.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_48);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state41.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_46);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state40.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_44);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state39.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_42);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state38.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_40);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state37.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_3E);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state36.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_3C);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state35.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_3A);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state34.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_38);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state33.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_36);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state32.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_34);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state31.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_32);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state30.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_30);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state29.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_2E);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state28.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_2C);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state27.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_2A);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state26.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_28);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state25.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_26);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state24.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_24);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state23.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_22);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state22.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_20);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state21.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_1E);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state20.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_1C);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state19.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_1A);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state18.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_18);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state17.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_16);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state16.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_14);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state15.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_12);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state14.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_10);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state13.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_E);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state12.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_C);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state11.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_A);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state10.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_8);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state9.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_6);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state8.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_4);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state7.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_2);
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state6.read())) {
        spike_in_address1 =  (sc_lv<8>) (ap_const_lv64_1);
    } else {
        spike_in_address1 =  (sc_lv<8>) ("XXXXXXXX");
    }
}

void snn_core_fc_last::thread_spike_in_ce0() {
    if (((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state5.read()) && 
          !(esl_seteq<1,1,1>(icmp_ln57_fu_5336_p2.read(), ap_const_lv1_0) && esl_seteq<1,1,1>(ap_const_logic_0, in_stream_TVALID.read()))) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state7.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state8.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state9.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state10.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state11.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state12.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state13.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state14.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state15.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state16.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state17.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state18.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state19.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state20.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state21.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state22.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state23.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state24.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state25.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state26.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state27.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state28.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state29.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state30.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state31.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state32.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state33.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state34.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state35.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state36.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state37.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state38.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state39.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state40.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state41.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state42.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state43.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state44.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state45.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state46.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state47.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state48.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state49.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state50.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state51.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state52.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state53.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state54.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state55.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state56.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state57.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state58.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state59.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state60.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state61.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state62.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state63.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state64.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state65.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state66.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state67.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state68.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state69.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state70.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state71.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state72.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state73.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state74.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state75.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state76.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state77.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state78.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state79.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state80.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state81.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state82.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state83.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state84.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state85.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state86.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state87.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state88.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state89.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state90.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state91.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state92.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state93.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state94.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state95.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state96.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state97.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state98.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state99.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state100.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state101.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state102.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state103.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state104.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state105.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state106.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state107.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state108.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state109.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state110.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state111.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state112.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state113.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state114.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state115.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state116.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state117.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state118.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state119.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state120.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state121.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state122.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state123.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state124.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state125.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state126.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state127.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state128.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state129.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state130.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state131.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state132.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state133.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state6.read()))) {
        spike_in_ce0 = ap_const_logic_1;
    } else {
        spike_in_ce0 = ap_const_logic_0;
    }
}

void snn_core_fc_last::thread_spike_in_ce1() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state7.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state8.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state9.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state10.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state11.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state12.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state13.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state14.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state15.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state16.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state17.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state18.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state19.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state20.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state21.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state22.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state23.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state24.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state25.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state26.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state27.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state28.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state29.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state30.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state31.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state32.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state33.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state34.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state35.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state36.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state37.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state38.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state39.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state40.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state41.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state42.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state43.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state44.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state45.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state46.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state47.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state48.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state49.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state50.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state51.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state52.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state53.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state54.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state55.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state56.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state57.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state58.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state59.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state60.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state61.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state62.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state63.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state64.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state65.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state66.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state67.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state68.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state69.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state70.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state71.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state72.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state73.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state74.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state75.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state76.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state77.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state78.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state79.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state80.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state81.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state82.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state83.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state84.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state85.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state86.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state87.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state88.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state89.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state90.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state91.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state92.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state93.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state94.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state95.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state96.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state97.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state98.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state99.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state100.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state101.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state102.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state103.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state104.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state105.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state106.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state107.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state108.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state109.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state110.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state111.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state112.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state113.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state114.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state115.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state116.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state117.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state118.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state119.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state120.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state121.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state122.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state123.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state124.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state125.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state126.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state127.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state128.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state129.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state130.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state131.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state132.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state133.read()) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state6.read()))) {
        spike_in_ce1 = ap_const_logic_1;
    } else {
        spike_in_ce1 = ap_const_logic_0;
    }
}

void snn_core_fc_last::thread_spike_in_d0() {
    spike_in_d0 = (!icmp_ln883_fu_5356_p2.read()[0].is_01())? sc_lv<32>(): ((icmp_ln883_fu_5356_p2.read()[0].to_bool())? ap_const_lv32_3F800000: ap_const_lv32_0);
}

void snn_core_fc_last::thread_spike_in_we0() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state5.read()) && 
         esl_seteq<1,1,1>(icmp_ln57_fu_5336_p2.read(), ap_const_lv1_0) && 
         !(esl_seteq<1,1,1>(icmp_ln57_fu_5336_p2.read(), ap_const_lv1_0) && esl_seteq<1,1,1>(ap_const_logic_0, in_stream_TVALID.read())))) {
        spike_in_we0 = ap_const_logic_1;
    } else {
        spike_in_we0 = ap_const_logic_0;
    }
}

void snn_core_fc_last::thread_t_fu_5330_p2() {
    t_fu_5330_p2 = (!t_0_reg_5078.read().is_01() || !ap_const_lv4_1.is_01())? sc_lv<4>(): (sc_biguint<4>(t_0_reg_5078.read()) + sc_biguint<4>(ap_const_lv4_1));
}

void snn_core_fc_last::thread_tmp_100_fu_6617_p3() {
    tmp_100_fu_6617_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_86_fu_6612_p2.read());
}

void snn_core_fc_last::thread_tmp_101_fu_6631_p3() {
    tmp_101_fu_6631_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_87_fu_6626_p2.read());
}

void snn_core_fc_last::thread_tmp_102_fu_6645_p3() {
    tmp_102_fu_6645_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_88_fu_6640_p2.read());
}

void snn_core_fc_last::thread_tmp_103_fu_6659_p3() {
    tmp_103_fu_6659_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_89_fu_6654_p2.read());
}

void snn_core_fc_last::thread_tmp_104_fu_6673_p3() {
    tmp_104_fu_6673_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_90_fu_6668_p2.read());
}

void snn_core_fc_last::thread_tmp_105_fu_6687_p3() {
    tmp_105_fu_6687_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_91_fu_6682_p2.read());
}

void snn_core_fc_last::thread_tmp_106_fu_6701_p3() {
    tmp_106_fu_6701_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_92_fu_6696_p2.read());
}

void snn_core_fc_last::thread_tmp_107_fu_6715_p3() {
    tmp_107_fu_6715_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_93_fu_6710_p2.read());
}

void snn_core_fc_last::thread_tmp_108_fu_6729_p3() {
    tmp_108_fu_6729_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_94_fu_6724_p2.read());
}

void snn_core_fc_last::thread_tmp_109_fu_6743_p3() {
    tmp_109_fu_6743_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_95_fu_6738_p2.read());
}

void snn_core_fc_last::thread_tmp_110_fu_6757_p3() {
    tmp_110_fu_6757_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_96_fu_6752_p2.read());
}

void snn_core_fc_last::thread_tmp_111_fu_6771_p3() {
    tmp_111_fu_6771_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_97_fu_6766_p2.read());
}

void snn_core_fc_last::thread_tmp_112_fu_6785_p3() {
    tmp_112_fu_6785_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_98_fu_6780_p2.read());
}

void snn_core_fc_last::thread_tmp_113_fu_6799_p3() {
    tmp_113_fu_6799_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_99_fu_6794_p2.read());
}

void snn_core_fc_last::thread_tmp_114_fu_6813_p3() {
    tmp_114_fu_6813_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_100_fu_6808_p2.read());
}

void snn_core_fc_last::thread_tmp_115_fu_6827_p3() {
    tmp_115_fu_6827_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_101_fu_6822_p2.read());
}

void snn_core_fc_last::thread_tmp_116_fu_6841_p3() {
    tmp_116_fu_6841_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_102_fu_6836_p2.read());
}

void snn_core_fc_last::thread_tmp_117_fu_6855_p3() {
    tmp_117_fu_6855_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_103_fu_6850_p2.read());
}

void snn_core_fc_last::thread_tmp_118_fu_6869_p3() {
    tmp_118_fu_6869_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_104_fu_6864_p2.read());
}

void snn_core_fc_last::thread_tmp_119_fu_6883_p3() {
    tmp_119_fu_6883_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_105_fu_6878_p2.read());
}

void snn_core_fc_last::thread_tmp_11_fu_8982_p4() {
    tmp_11_fu_8982_p4 = bitcast_ln16_fu_8978_p1.read().range(30, 23);
}

void snn_core_fc_last::thread_tmp_120_fu_6897_p3() {
    tmp_120_fu_6897_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_106_fu_6892_p2.read());
}

void snn_core_fc_last::thread_tmp_121_fu_6911_p3() {
    tmp_121_fu_6911_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_107_fu_6906_p2.read());
}

void snn_core_fc_last::thread_tmp_122_fu_6925_p3() {
    tmp_122_fu_6925_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_108_fu_6920_p2.read());
}

void snn_core_fc_last::thread_tmp_123_fu_6939_p3() {
    tmp_123_fu_6939_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_109_fu_6934_p2.read());
}

void snn_core_fc_last::thread_tmp_124_fu_6953_p3() {
    tmp_124_fu_6953_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_110_fu_6948_p2.read());
}

void snn_core_fc_last::thread_tmp_125_fu_6967_p3() {
    tmp_125_fu_6967_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_111_fu_6962_p2.read());
}

void snn_core_fc_last::thread_tmp_126_fu_6981_p3() {
    tmp_126_fu_6981_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_112_fu_6976_p2.read());
}

void snn_core_fc_last::thread_tmp_127_fu_6995_p3() {
    tmp_127_fu_6995_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_113_fu_6990_p2.read());
}

void snn_core_fc_last::thread_tmp_128_fu_7009_p3() {
    tmp_128_fu_7009_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_114_fu_7004_p2.read());
}

void snn_core_fc_last::thread_tmp_129_fu_7023_p3() {
    tmp_129_fu_7023_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_115_fu_7018_p2.read());
}

void snn_core_fc_last::thread_tmp_130_fu_7037_p3() {
    tmp_130_fu_7037_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_116_fu_7032_p2.read());
}

void snn_core_fc_last::thread_tmp_131_fu_7051_p3() {
    tmp_131_fu_7051_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_117_fu_7046_p2.read());
}

void snn_core_fc_last::thread_tmp_132_fu_7065_p3() {
    tmp_132_fu_7065_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_118_fu_7060_p2.read());
}

void snn_core_fc_last::thread_tmp_133_fu_7079_p3() {
    tmp_133_fu_7079_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_119_fu_7074_p2.read());
}

void snn_core_fc_last::thread_tmp_134_fu_7093_p3() {
    tmp_134_fu_7093_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_120_fu_7088_p2.read());
}

void snn_core_fc_last::thread_tmp_135_fu_7107_p3() {
    tmp_135_fu_7107_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_121_fu_7102_p2.read());
}

void snn_core_fc_last::thread_tmp_136_fu_7121_p3() {
    tmp_136_fu_7121_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_122_fu_7116_p2.read());
}

void snn_core_fc_last::thread_tmp_137_fu_7135_p3() {
    tmp_137_fu_7135_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_123_fu_7130_p2.read());
}

void snn_core_fc_last::thread_tmp_138_fu_7149_p3() {
    tmp_138_fu_7149_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_124_fu_7144_p2.read());
}

void snn_core_fc_last::thread_tmp_139_fu_7163_p3() {
    tmp_139_fu_7163_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_125_fu_7158_p2.read());
}

void snn_core_fc_last::thread_tmp_13_fu_5394_p3() {
    tmp_13_fu_5394_p3 = esl_concat<4,8>(ap_phi_mux_o1_0_phi_fu_5104_p4.read(), ap_const_lv8_0);
}

void snn_core_fc_last::thread_tmp_140_fu_7177_p3() {
    tmp_140_fu_7177_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_126_fu_7172_p2.read());
}

void snn_core_fc_last::thread_tmp_141_fu_7191_p3() {
    tmp_141_fu_7191_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_127_fu_7186_p2.read());
}

void snn_core_fc_last::thread_tmp_142_fu_7205_p3() {
    tmp_142_fu_7205_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_128_fu_7200_p2.read());
}

void snn_core_fc_last::thread_tmp_143_fu_7219_p3() {
    tmp_143_fu_7219_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_129_fu_7214_p2.read());
}

void snn_core_fc_last::thread_tmp_144_fu_7233_p3() {
    tmp_144_fu_7233_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_130_fu_7228_p2.read());
}

void snn_core_fc_last::thread_tmp_145_fu_7247_p3() {
    tmp_145_fu_7247_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_131_fu_7242_p2.read());
}

void snn_core_fc_last::thread_tmp_146_fu_7261_p3() {
    tmp_146_fu_7261_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_132_fu_7256_p2.read());
}

void snn_core_fc_last::thread_tmp_147_fu_7275_p3() {
    tmp_147_fu_7275_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_133_fu_7270_p2.read());
}

void snn_core_fc_last::thread_tmp_148_fu_7289_p3() {
    tmp_148_fu_7289_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_134_fu_7284_p2.read());
}

void snn_core_fc_last::thread_tmp_149_fu_7303_p3() {
    tmp_149_fu_7303_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_135_fu_7298_p2.read());
}

void snn_core_fc_last::thread_tmp_14_fu_5413_p3() {
    tmp_14_fu_5413_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_fu_5407_p2.read());
}

void snn_core_fc_last::thread_tmp_150_fu_7317_p3() {
    tmp_150_fu_7317_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_136_fu_7312_p2.read());
}

void snn_core_fc_last::thread_tmp_151_fu_7331_p3() {
    tmp_151_fu_7331_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_137_fu_7326_p2.read());
}

void snn_core_fc_last::thread_tmp_152_fu_7345_p3() {
    tmp_152_fu_7345_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_138_fu_7340_p2.read());
}

void snn_core_fc_last::thread_tmp_153_fu_7359_p3() {
    tmp_153_fu_7359_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_139_fu_7354_p2.read());
}

void snn_core_fc_last::thread_tmp_154_fu_7373_p3() {
    tmp_154_fu_7373_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_140_fu_7368_p2.read());
}

void snn_core_fc_last::thread_tmp_155_fu_7387_p3() {
    tmp_155_fu_7387_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_141_fu_7382_p2.read());
}

void snn_core_fc_last::thread_tmp_156_fu_7401_p3() {
    tmp_156_fu_7401_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_142_fu_7396_p2.read());
}

void snn_core_fc_last::thread_tmp_157_fu_7415_p3() {
    tmp_157_fu_7415_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_143_fu_7410_p2.read());
}

void snn_core_fc_last::thread_tmp_158_fu_7429_p3() {
    tmp_158_fu_7429_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_144_fu_7424_p2.read());
}

void snn_core_fc_last::thread_tmp_159_fu_7443_p3() {
    tmp_159_fu_7443_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_145_fu_7438_p2.read());
}

void snn_core_fc_last::thread_tmp_15_fu_5427_p3() {
    tmp_15_fu_5427_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_1_fu_5422_p2.read());
}

void snn_core_fc_last::thread_tmp_160_fu_7457_p3() {
    tmp_160_fu_7457_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_146_fu_7452_p2.read());
}

void snn_core_fc_last::thread_tmp_161_fu_7471_p3() {
    tmp_161_fu_7471_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_147_fu_7466_p2.read());
}

void snn_core_fc_last::thread_tmp_162_fu_7485_p3() {
    tmp_162_fu_7485_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_148_fu_7480_p2.read());
}

void snn_core_fc_last::thread_tmp_163_fu_7499_p3() {
    tmp_163_fu_7499_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_149_fu_7494_p2.read());
}

void snn_core_fc_last::thread_tmp_164_fu_7513_p3() {
    tmp_164_fu_7513_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_150_fu_7508_p2.read());
}

void snn_core_fc_last::thread_tmp_165_fu_7527_p3() {
    tmp_165_fu_7527_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_151_fu_7522_p2.read());
}

void snn_core_fc_last::thread_tmp_166_fu_7541_p3() {
    tmp_166_fu_7541_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_152_fu_7536_p2.read());
}

void snn_core_fc_last::thread_tmp_167_fu_7555_p3() {
    tmp_167_fu_7555_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_153_fu_7550_p2.read());
}

void snn_core_fc_last::thread_tmp_168_fu_7569_p3() {
    tmp_168_fu_7569_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_154_fu_7564_p2.read());
}

void snn_core_fc_last::thread_tmp_169_fu_7583_p3() {
    tmp_169_fu_7583_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_155_fu_7578_p2.read());
}

void snn_core_fc_last::thread_tmp_16_fu_5441_p3() {
    tmp_16_fu_5441_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_2_fu_5436_p2.read());
}

void snn_core_fc_last::thread_tmp_170_fu_7597_p3() {
    tmp_170_fu_7597_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_156_fu_7592_p2.read());
}

void snn_core_fc_last::thread_tmp_171_fu_7611_p3() {
    tmp_171_fu_7611_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_157_fu_7606_p2.read());
}

void snn_core_fc_last::thread_tmp_172_fu_7625_p3() {
    tmp_172_fu_7625_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_158_fu_7620_p2.read());
}

void snn_core_fc_last::thread_tmp_173_fu_7639_p3() {
    tmp_173_fu_7639_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_159_fu_7634_p2.read());
}

void snn_core_fc_last::thread_tmp_174_fu_7653_p3() {
    tmp_174_fu_7653_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_160_fu_7648_p2.read());
}

void snn_core_fc_last::thread_tmp_175_fu_7667_p3() {
    tmp_175_fu_7667_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_161_fu_7662_p2.read());
}

void snn_core_fc_last::thread_tmp_176_fu_7681_p3() {
    tmp_176_fu_7681_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_162_fu_7676_p2.read());
}

void snn_core_fc_last::thread_tmp_177_fu_7695_p3() {
    tmp_177_fu_7695_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_163_fu_7690_p2.read());
}

void snn_core_fc_last::thread_tmp_178_fu_7709_p3() {
    tmp_178_fu_7709_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_164_fu_7704_p2.read());
}

void snn_core_fc_last::thread_tmp_179_fu_7723_p3() {
    tmp_179_fu_7723_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_165_fu_7718_p2.read());
}

void snn_core_fc_last::thread_tmp_17_fu_5455_p3() {
    tmp_17_fu_5455_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_3_fu_5450_p2.read());
}

void snn_core_fc_last::thread_tmp_180_fu_7737_p3() {
    tmp_180_fu_7737_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_166_fu_7732_p2.read());
}

void snn_core_fc_last::thread_tmp_181_fu_7751_p3() {
    tmp_181_fu_7751_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_167_fu_7746_p2.read());
}

void snn_core_fc_last::thread_tmp_182_fu_7765_p3() {
    tmp_182_fu_7765_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_168_fu_7760_p2.read());
}

void snn_core_fc_last::thread_tmp_183_fu_7779_p3() {
    tmp_183_fu_7779_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_169_fu_7774_p2.read());
}

void snn_core_fc_last::thread_tmp_184_fu_7793_p3() {
    tmp_184_fu_7793_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_170_fu_7788_p2.read());
}

void snn_core_fc_last::thread_tmp_185_fu_7807_p3() {
    tmp_185_fu_7807_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_171_fu_7802_p2.read());
}

void snn_core_fc_last::thread_tmp_186_fu_7821_p3() {
    tmp_186_fu_7821_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_172_fu_7816_p2.read());
}

void snn_core_fc_last::thread_tmp_187_fu_7835_p3() {
    tmp_187_fu_7835_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_173_fu_7830_p2.read());
}

void snn_core_fc_last::thread_tmp_188_fu_7849_p3() {
    tmp_188_fu_7849_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_174_fu_7844_p2.read());
}

void snn_core_fc_last::thread_tmp_189_fu_7863_p3() {
    tmp_189_fu_7863_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_175_fu_7858_p2.read());
}

void snn_core_fc_last::thread_tmp_18_fu_5469_p3() {
    tmp_18_fu_5469_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_4_fu_5464_p2.read());
}

void snn_core_fc_last::thread_tmp_190_fu_7877_p3() {
    tmp_190_fu_7877_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_176_fu_7872_p2.read());
}

void snn_core_fc_last::thread_tmp_191_fu_7891_p3() {
    tmp_191_fu_7891_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_177_fu_7886_p2.read());
}

void snn_core_fc_last::thread_tmp_192_fu_7905_p3() {
    tmp_192_fu_7905_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_178_fu_7900_p2.read());
}

void snn_core_fc_last::thread_tmp_193_fu_7919_p3() {
    tmp_193_fu_7919_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_179_fu_7914_p2.read());
}

void snn_core_fc_last::thread_tmp_194_fu_7933_p3() {
    tmp_194_fu_7933_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_180_fu_7928_p2.read());
}

void snn_core_fc_last::thread_tmp_195_fu_7947_p3() {
    tmp_195_fu_7947_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_181_fu_7942_p2.read());
}

void snn_core_fc_last::thread_tmp_196_fu_7961_p3() {
    tmp_196_fu_7961_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_182_fu_7956_p2.read());
}

void snn_core_fc_last::thread_tmp_197_fu_7975_p3() {
    tmp_197_fu_7975_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_183_fu_7970_p2.read());
}

void snn_core_fc_last::thread_tmp_198_fu_7989_p3() {
    tmp_198_fu_7989_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_184_fu_7984_p2.read());
}

void snn_core_fc_last::thread_tmp_199_fu_8003_p3() {
    tmp_199_fu_8003_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_185_fu_7998_p2.read());
}

void snn_core_fc_last::thread_tmp_19_fu_5483_p3() {
    tmp_19_fu_5483_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_5_fu_5478_p2.read());
}

void snn_core_fc_last::thread_tmp_200_fu_8017_p3() {
    tmp_200_fu_8017_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_186_fu_8012_p2.read());
}

void snn_core_fc_last::thread_tmp_201_fu_8031_p3() {
    tmp_201_fu_8031_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_187_fu_8026_p2.read());
}

void snn_core_fc_last::thread_tmp_202_fu_8045_p3() {
    tmp_202_fu_8045_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_188_fu_8040_p2.read());
}

void snn_core_fc_last::thread_tmp_203_fu_8059_p3() {
    tmp_203_fu_8059_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_189_fu_8054_p2.read());
}

void snn_core_fc_last::thread_tmp_204_fu_8073_p3() {
    tmp_204_fu_8073_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_190_fu_8068_p2.read());
}

void snn_core_fc_last::thread_tmp_205_fu_8087_p3() {
    tmp_205_fu_8087_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_191_fu_8082_p2.read());
}

void snn_core_fc_last::thread_tmp_206_fu_8101_p3() {
    tmp_206_fu_8101_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_192_fu_8096_p2.read());
}

void snn_core_fc_last::thread_tmp_207_fu_8115_p3() {
    tmp_207_fu_8115_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_193_fu_8110_p2.read());
}

void snn_core_fc_last::thread_tmp_208_fu_8129_p3() {
    tmp_208_fu_8129_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_194_fu_8124_p2.read());
}

void snn_core_fc_last::thread_tmp_209_fu_8143_p3() {
    tmp_209_fu_8143_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_195_fu_8138_p2.read());
}

void snn_core_fc_last::thread_tmp_20_fu_5497_p3() {
    tmp_20_fu_5497_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_6_fu_5492_p2.read());
}

void snn_core_fc_last::thread_tmp_210_fu_8157_p3() {
    tmp_210_fu_8157_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_196_fu_8152_p2.read());
}

void snn_core_fc_last::thread_tmp_211_fu_8171_p3() {
    tmp_211_fu_8171_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_197_fu_8166_p2.read());
}

void snn_core_fc_last::thread_tmp_212_fu_8185_p3() {
    tmp_212_fu_8185_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_198_fu_8180_p2.read());
}

void snn_core_fc_last::thread_tmp_213_fu_8199_p3() {
    tmp_213_fu_8199_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_199_fu_8194_p2.read());
}

void snn_core_fc_last::thread_tmp_214_fu_8213_p3() {
    tmp_214_fu_8213_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_200_fu_8208_p2.read());
}

void snn_core_fc_last::thread_tmp_215_fu_8227_p3() {
    tmp_215_fu_8227_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_201_fu_8222_p2.read());
}

void snn_core_fc_last::thread_tmp_216_fu_8241_p3() {
    tmp_216_fu_8241_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_202_fu_8236_p2.read());
}

void snn_core_fc_last::thread_tmp_217_fu_8255_p3() {
    tmp_217_fu_8255_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_203_fu_8250_p2.read());
}

void snn_core_fc_last::thread_tmp_218_fu_8269_p3() {
    tmp_218_fu_8269_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_204_fu_8264_p2.read());
}

void snn_core_fc_last::thread_tmp_219_fu_8283_p3() {
    tmp_219_fu_8283_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_205_fu_8278_p2.read());
}

void snn_core_fc_last::thread_tmp_21_fu_5511_p3() {
    tmp_21_fu_5511_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_7_fu_5506_p2.read());
}

void snn_core_fc_last::thread_tmp_220_fu_8297_p3() {
    tmp_220_fu_8297_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_206_fu_8292_p2.read());
}

void snn_core_fc_last::thread_tmp_221_fu_8311_p3() {
    tmp_221_fu_8311_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_207_fu_8306_p2.read());
}

void snn_core_fc_last::thread_tmp_222_fu_8325_p3() {
    tmp_222_fu_8325_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_208_fu_8320_p2.read());
}

void snn_core_fc_last::thread_tmp_223_fu_8339_p3() {
    tmp_223_fu_8339_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_209_fu_8334_p2.read());
}

void snn_core_fc_last::thread_tmp_224_fu_8353_p3() {
    tmp_224_fu_8353_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_210_fu_8348_p2.read());
}

void snn_core_fc_last::thread_tmp_225_fu_8367_p3() {
    tmp_225_fu_8367_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_211_fu_8362_p2.read());
}

void snn_core_fc_last::thread_tmp_226_fu_8381_p3() {
    tmp_226_fu_8381_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_212_fu_8376_p2.read());
}

void snn_core_fc_last::thread_tmp_227_fu_8395_p3() {
    tmp_227_fu_8395_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_213_fu_8390_p2.read());
}

void snn_core_fc_last::thread_tmp_228_fu_8409_p3() {
    tmp_228_fu_8409_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_214_fu_8404_p2.read());
}

void snn_core_fc_last::thread_tmp_229_fu_8423_p3() {
    tmp_229_fu_8423_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_215_fu_8418_p2.read());
}

void snn_core_fc_last::thread_tmp_22_fu_5525_p3() {
    tmp_22_fu_5525_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_8_fu_5520_p2.read());
}

void snn_core_fc_last::thread_tmp_230_fu_8437_p3() {
    tmp_230_fu_8437_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_216_fu_8432_p2.read());
}

void snn_core_fc_last::thread_tmp_231_fu_8451_p3() {
    tmp_231_fu_8451_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_217_fu_8446_p2.read());
}

void snn_core_fc_last::thread_tmp_232_fu_8465_p3() {
    tmp_232_fu_8465_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_218_fu_8460_p2.read());
}

void snn_core_fc_last::thread_tmp_233_fu_8479_p3() {
    tmp_233_fu_8479_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_219_fu_8474_p2.read());
}

void snn_core_fc_last::thread_tmp_234_fu_8493_p3() {
    tmp_234_fu_8493_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_220_fu_8488_p2.read());
}

void snn_core_fc_last::thread_tmp_235_fu_8507_p3() {
    tmp_235_fu_8507_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_221_fu_8502_p2.read());
}

void snn_core_fc_last::thread_tmp_236_fu_8521_p3() {
    tmp_236_fu_8521_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_222_fu_8516_p2.read());
}

void snn_core_fc_last::thread_tmp_237_fu_8535_p3() {
    tmp_237_fu_8535_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_223_fu_8530_p2.read());
}

void snn_core_fc_last::thread_tmp_238_fu_8549_p3() {
    tmp_238_fu_8549_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_224_fu_8544_p2.read());
}

void snn_core_fc_last::thread_tmp_239_fu_8563_p3() {
    tmp_239_fu_8563_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_225_fu_8558_p2.read());
}

void snn_core_fc_last::thread_tmp_23_fu_5539_p3() {
    tmp_23_fu_5539_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_9_fu_5534_p2.read());
}

void snn_core_fc_last::thread_tmp_240_fu_8577_p3() {
    tmp_240_fu_8577_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_226_fu_8572_p2.read());
}

void snn_core_fc_last::thread_tmp_241_fu_8591_p3() {
    tmp_241_fu_8591_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_227_fu_8586_p2.read());
}

void snn_core_fc_last::thread_tmp_242_fu_8605_p3() {
    tmp_242_fu_8605_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_228_fu_8600_p2.read());
}

void snn_core_fc_last::thread_tmp_243_fu_8619_p3() {
    tmp_243_fu_8619_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_229_fu_8614_p2.read());
}

void snn_core_fc_last::thread_tmp_244_fu_8633_p3() {
    tmp_244_fu_8633_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_230_fu_8628_p2.read());
}

void snn_core_fc_last::thread_tmp_245_fu_8647_p3() {
    tmp_245_fu_8647_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_231_fu_8642_p2.read());
}

void snn_core_fc_last::thread_tmp_246_fu_8661_p3() {
    tmp_246_fu_8661_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_232_fu_8656_p2.read());
}

void snn_core_fc_last::thread_tmp_247_fu_8675_p3() {
    tmp_247_fu_8675_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_233_fu_8670_p2.read());
}

void snn_core_fc_last::thread_tmp_248_fu_8689_p3() {
    tmp_248_fu_8689_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_234_fu_8684_p2.read());
}

void snn_core_fc_last::thread_tmp_249_fu_8703_p3() {
    tmp_249_fu_8703_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_235_fu_8698_p2.read());
}

void snn_core_fc_last::thread_tmp_24_fu_5553_p3() {
    tmp_24_fu_5553_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_10_fu_5548_p2.read());
}

void snn_core_fc_last::thread_tmp_250_fu_8717_p3() {
    tmp_250_fu_8717_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_236_fu_8712_p2.read());
}

void snn_core_fc_last::thread_tmp_251_fu_8731_p3() {
    tmp_251_fu_8731_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_237_fu_8726_p2.read());
}

void snn_core_fc_last::thread_tmp_252_fu_8745_p3() {
    tmp_252_fu_8745_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_238_fu_8740_p2.read());
}

void snn_core_fc_last::thread_tmp_253_fu_8759_p3() {
    tmp_253_fu_8759_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_239_fu_8754_p2.read());
}

void snn_core_fc_last::thread_tmp_254_fu_8773_p3() {
    tmp_254_fu_8773_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_240_fu_8768_p2.read());
}

void snn_core_fc_last::thread_tmp_255_fu_8787_p3() {
    tmp_255_fu_8787_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_241_fu_8782_p2.read());
}

void snn_core_fc_last::thread_tmp_256_fu_8801_p3() {
    tmp_256_fu_8801_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_242_fu_8796_p2.read());
}

void snn_core_fc_last::thread_tmp_257_fu_8815_p3() {
    tmp_257_fu_8815_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_243_fu_8810_p2.read());
}

void snn_core_fc_last::thread_tmp_258_fu_8829_p3() {
    tmp_258_fu_8829_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_244_fu_8824_p2.read());
}

void snn_core_fc_last::thread_tmp_259_fu_8843_p3() {
    tmp_259_fu_8843_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_245_fu_8838_p2.read());
}

void snn_core_fc_last::thread_tmp_25_fu_5567_p3() {
    tmp_25_fu_5567_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_11_fu_5562_p2.read());
}

void snn_core_fc_last::thread_tmp_260_fu_8857_p3() {
    tmp_260_fu_8857_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_246_fu_8852_p2.read());
}

void snn_core_fc_last::thread_tmp_261_fu_8871_p3() {
    tmp_261_fu_8871_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_247_fu_8866_p2.read());
}

void snn_core_fc_last::thread_tmp_262_fu_8885_p3() {
    tmp_262_fu_8885_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_248_fu_8880_p2.read());
}

void snn_core_fc_last::thread_tmp_263_fu_8899_p3() {
    tmp_263_fu_8899_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_249_fu_8894_p2.read());
}

void snn_core_fc_last::thread_tmp_264_fu_8913_p3() {
    tmp_264_fu_8913_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_250_fu_8908_p2.read());
}

void snn_core_fc_last::thread_tmp_265_fu_8927_p3() {
    tmp_265_fu_8927_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_251_fu_8922_p2.read());
}

void snn_core_fc_last::thread_tmp_266_fu_8941_p3() {
    tmp_266_fu_8941_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_252_fu_8936_p2.read());
}

void snn_core_fc_last::thread_tmp_267_fu_8955_p3() {
    tmp_267_fu_8955_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_253_fu_8950_p2.read());
}

void snn_core_fc_last::thread_tmp_268_fu_8969_p3() {
    tmp_268_fu_8969_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_254_fu_8964_p2.read());
}

void snn_core_fc_last::thread_tmp_26_fu_5581_p3() {
    tmp_26_fu_5581_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_12_fu_5576_p2.read());
}

void snn_core_fc_last::thread_tmp_27_fu_5595_p3() {
    tmp_27_fu_5595_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_13_fu_5590_p2.read());
}

void snn_core_fc_last::thread_tmp_28_fu_5609_p3() {
    tmp_28_fu_5609_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_14_fu_5604_p2.read());
}

void snn_core_fc_last::thread_tmp_29_fu_5623_p3() {
    tmp_29_fu_5623_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_15_fu_5618_p2.read());
}

void snn_core_fc_last::thread_tmp_30_fu_5637_p3() {
    tmp_30_fu_5637_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_16_fu_5632_p2.read());
}

void snn_core_fc_last::thread_tmp_31_fu_5651_p3() {
    tmp_31_fu_5651_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_17_fu_5646_p2.read());
}

void snn_core_fc_last::thread_tmp_32_fu_5665_p3() {
    tmp_32_fu_5665_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_18_fu_5660_p2.read());
}

void snn_core_fc_last::thread_tmp_33_fu_5679_p3() {
    tmp_33_fu_5679_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_19_fu_5674_p2.read());
}

void snn_core_fc_last::thread_tmp_34_fu_5693_p3() {
    tmp_34_fu_5693_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_20_fu_5688_p2.read());
}

void snn_core_fc_last::thread_tmp_35_fu_5707_p3() {
    tmp_35_fu_5707_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_21_fu_5702_p2.read());
}

void snn_core_fc_last::thread_tmp_36_fu_5721_p3() {
    tmp_36_fu_5721_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_22_fu_5716_p2.read());
}

void snn_core_fc_last::thread_tmp_37_fu_5735_p3() {
    tmp_37_fu_5735_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_23_fu_5730_p2.read());
}

void snn_core_fc_last::thread_tmp_38_fu_5749_p3() {
    tmp_38_fu_5749_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_24_fu_5744_p2.read());
}

void snn_core_fc_last::thread_tmp_39_fu_5763_p3() {
    tmp_39_fu_5763_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_25_fu_5758_p2.read());
}

void snn_core_fc_last::thread_tmp_40_fu_5777_p3() {
    tmp_40_fu_5777_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_26_fu_5772_p2.read());
}

void snn_core_fc_last::thread_tmp_41_fu_5791_p3() {
    tmp_41_fu_5791_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_27_fu_5786_p2.read());
}

void snn_core_fc_last::thread_tmp_42_fu_5805_p3() {
    tmp_42_fu_5805_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_28_fu_5800_p2.read());
}

void snn_core_fc_last::thread_tmp_43_fu_5819_p3() {
    tmp_43_fu_5819_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_29_fu_5814_p2.read());
}

void snn_core_fc_last::thread_tmp_44_fu_5833_p3() {
    tmp_44_fu_5833_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_30_fu_5828_p2.read());
}

void snn_core_fc_last::thread_tmp_45_fu_5847_p3() {
    tmp_45_fu_5847_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_31_fu_5842_p2.read());
}

void snn_core_fc_last::thread_tmp_46_fu_5861_p3() {
    tmp_46_fu_5861_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_32_fu_5856_p2.read());
}

void snn_core_fc_last::thread_tmp_47_fu_5875_p3() {
    tmp_47_fu_5875_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_33_fu_5870_p2.read());
}

void snn_core_fc_last::thread_tmp_48_fu_5889_p3() {
    tmp_48_fu_5889_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_34_fu_5884_p2.read());
}

void snn_core_fc_last::thread_tmp_49_fu_5903_p3() {
    tmp_49_fu_5903_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_35_fu_5898_p2.read());
}

void snn_core_fc_last::thread_tmp_4_fu_9075_p4() {
    tmp_4_fu_9075_p4 = bitcast_ln90_1_fu_9071_p1.read().range(30, 23);
}

void snn_core_fc_last::thread_tmp_50_fu_5917_p3() {
    tmp_50_fu_5917_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_36_fu_5912_p2.read());
}

void snn_core_fc_last::thread_tmp_51_fu_5931_p3() {
    tmp_51_fu_5931_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_37_fu_5926_p2.read());
}

void snn_core_fc_last::thread_tmp_52_fu_5945_p3() {
    tmp_52_fu_5945_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_38_fu_5940_p2.read());
}

void snn_core_fc_last::thread_tmp_53_fu_5959_p3() {
    tmp_53_fu_5959_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_39_fu_5954_p2.read());
}

void snn_core_fc_last::thread_tmp_54_fu_5973_p3() {
    tmp_54_fu_5973_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_40_fu_5968_p2.read());
}

void snn_core_fc_last::thread_tmp_55_fu_5987_p3() {
    tmp_55_fu_5987_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_41_fu_5982_p2.read());
}

void snn_core_fc_last::thread_tmp_56_fu_6001_p3() {
    tmp_56_fu_6001_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_42_fu_5996_p2.read());
}

void snn_core_fc_last::thread_tmp_57_fu_6015_p3() {
    tmp_57_fu_6015_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_43_fu_6010_p2.read());
}

void snn_core_fc_last::thread_tmp_58_fu_6029_p3() {
    tmp_58_fu_6029_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_44_fu_6024_p2.read());
}

void snn_core_fc_last::thread_tmp_59_fu_6043_p3() {
    tmp_59_fu_6043_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_45_fu_6038_p2.read());
}

void snn_core_fc_last::thread_tmp_60_fu_6057_p3() {
    tmp_60_fu_6057_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_46_fu_6052_p2.read());
}

void snn_core_fc_last::thread_tmp_61_fu_6071_p3() {
    tmp_61_fu_6071_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_47_fu_6066_p2.read());
}

void snn_core_fc_last::thread_tmp_62_fu_6085_p3() {
    tmp_62_fu_6085_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_48_fu_6080_p2.read());
}

void snn_core_fc_last::thread_tmp_63_fu_6099_p3() {
    tmp_63_fu_6099_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_49_fu_6094_p2.read());
}

void snn_core_fc_last::thread_tmp_64_fu_6113_p3() {
    tmp_64_fu_6113_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_50_fu_6108_p2.read());
}

void snn_core_fc_last::thread_tmp_65_fu_6127_p3() {
    tmp_65_fu_6127_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_51_fu_6122_p2.read());
}

void snn_core_fc_last::thread_tmp_66_fu_6141_p3() {
    tmp_66_fu_6141_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_52_fu_6136_p2.read());
}

void snn_core_fc_last::thread_tmp_67_fu_6155_p3() {
    tmp_67_fu_6155_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_53_fu_6150_p2.read());
}

void snn_core_fc_last::thread_tmp_68_fu_6169_p3() {
    tmp_68_fu_6169_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_54_fu_6164_p2.read());
}

void snn_core_fc_last::thread_tmp_69_fu_6183_p3() {
    tmp_69_fu_6183_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_55_fu_6178_p2.read());
}

void snn_core_fc_last::thread_tmp_70_fu_6197_p3() {
    tmp_70_fu_6197_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_56_fu_6192_p2.read());
}

void snn_core_fc_last::thread_tmp_71_fu_6211_p3() {
    tmp_71_fu_6211_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_57_fu_6206_p2.read());
}

void snn_core_fc_last::thread_tmp_72_fu_6225_p3() {
    tmp_72_fu_6225_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_58_fu_6220_p2.read());
}

void snn_core_fc_last::thread_tmp_73_fu_6239_p3() {
    tmp_73_fu_6239_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_59_fu_6234_p2.read());
}

void snn_core_fc_last::thread_tmp_74_fu_6253_p3() {
    tmp_74_fu_6253_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_60_fu_6248_p2.read());
}

void snn_core_fc_last::thread_tmp_75_fu_6267_p3() {
    tmp_75_fu_6267_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_61_fu_6262_p2.read());
}

void snn_core_fc_last::thread_tmp_76_fu_6281_p3() {
    tmp_76_fu_6281_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_62_fu_6276_p2.read());
}

void snn_core_fc_last::thread_tmp_77_fu_6295_p3() {
    tmp_77_fu_6295_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_63_fu_6290_p2.read());
}

void snn_core_fc_last::thread_tmp_78_fu_6309_p3() {
    tmp_78_fu_6309_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_64_fu_6304_p2.read());
}

void snn_core_fc_last::thread_tmp_79_fu_6323_p3() {
    tmp_79_fu_6323_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_65_fu_6318_p2.read());
}

void snn_core_fc_last::thread_tmp_80_fu_6337_p3() {
    tmp_80_fu_6337_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_66_fu_6332_p2.read());
}

void snn_core_fc_last::thread_tmp_81_fu_6351_p3() {
    tmp_81_fu_6351_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_67_fu_6346_p2.read());
}

void snn_core_fc_last::thread_tmp_82_fu_6365_p3() {
    tmp_82_fu_6365_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_68_fu_6360_p2.read());
}

void snn_core_fc_last::thread_tmp_83_fu_6379_p3() {
    tmp_83_fu_6379_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_69_fu_6374_p2.read());
}

void snn_core_fc_last::thread_tmp_84_fu_6393_p3() {
    tmp_84_fu_6393_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_70_fu_6388_p2.read());
}

void snn_core_fc_last::thread_tmp_85_fu_6407_p3() {
    tmp_85_fu_6407_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_71_fu_6402_p2.read());
}

void snn_core_fc_last::thread_tmp_86_fu_6421_p3() {
    tmp_86_fu_6421_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_72_fu_6416_p2.read());
}

void snn_core_fc_last::thread_tmp_87_fu_6435_p3() {
    tmp_87_fu_6435_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_73_fu_6430_p2.read());
}

void snn_core_fc_last::thread_tmp_88_fu_6449_p3() {
    tmp_88_fu_6449_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_74_fu_6444_p2.read());
}

void snn_core_fc_last::thread_tmp_89_fu_6463_p3() {
    tmp_89_fu_6463_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_75_fu_6458_p2.read());
}

void snn_core_fc_last::thread_tmp_90_fu_6477_p3() {
    tmp_90_fu_6477_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_76_fu_6472_p2.read());
}

void snn_core_fc_last::thread_tmp_91_fu_6491_p3() {
    tmp_91_fu_6491_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_77_fu_6486_p2.read());
}

void snn_core_fc_last::thread_tmp_92_fu_6505_p3() {
    tmp_92_fu_6505_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_78_fu_6500_p2.read());
}

void snn_core_fc_last::thread_tmp_93_fu_6519_p3() {
    tmp_93_fu_6519_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_79_fu_6514_p2.read());
}

void snn_core_fc_last::thread_tmp_94_fu_6533_p3() {
    tmp_94_fu_6533_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_80_fu_6528_p2.read());
}

void snn_core_fc_last::thread_tmp_95_fu_6547_p3() {
    tmp_95_fu_6547_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_81_fu_6542_p2.read());
}

void snn_core_fc_last::thread_tmp_96_fu_6561_p3() {
    tmp_96_fu_6561_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_82_fu_6556_p2.read());
}

void snn_core_fc_last::thread_tmp_97_fu_6575_p3() {
    tmp_97_fu_6575_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_83_fu_6570_p2.read());
}

void snn_core_fc_last::thread_tmp_98_fu_6589_p3() {
    tmp_98_fu_6589_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_84_fu_6584_p2.read());
}

void snn_core_fc_last::thread_tmp_99_fu_6603_p3() {
    tmp_99_fu_6603_p3 = esl_concat<52,12>(ap_const_lv52_0, or_ln74_85_fu_6598_p2.read());
}

void snn_core_fc_last::thread_tmp_fu_9057_p4() {
    tmp_fu_9057_p4 = bitcast_ln90_fu_9053_p1.read().range(30, 23);
}

void snn_core_fc_last::thread_trunc_ln16_fu_8992_p1() {
    trunc_ln16_fu_8992_p1 = bitcast_ln16_fu_8978_p1.read().range(23-1, 0);
}

void snn_core_fc_last::thread_trunc_ln90_1_fu_9085_p1() {
    trunc_ln90_1_fu_9085_p1 = bitcast_ln90_1_fu_9071_p1.read().range(23-1, 0);
}

void snn_core_fc_last::thread_trunc_ln90_fu_9067_p1() {
    trunc_ln90_fu_9067_p1 = bitcast_ln90_fu_9053_p1.read().range(23-1, 0);
}

void snn_core_fc_last::thread_v_V_fu_5352_p1() {
    v_V_fu_5352_p1 = in_stream_TDATA.read().range(8-1, 0);
}

void snn_core_fc_last::thread_zext_ln44_fu_5318_p1() {
    zext_ln44_fu_5318_p1 = esl_zext<64,4>(o_0_reg_5067.read());
}

void snn_core_fc_last::thread_zext_ln62_fu_5371_p1() {
    zext_ln62_fu_5371_p1 = esl_zext<64,9>(i_0_reg_5089.read());
}

void snn_core_fc_last::thread_zext_ln74_1_fu_5402_p1() {
    zext_ln74_1_fu_5402_p1 = esl_zext<64,12>(tmp_13_fu_5394_p3.read());
}

void snn_core_fc_last::thread_zext_ln74_fu_5388_p1() {
    zext_ln74_fu_5388_p1 = esl_zext<64,4>(ap_phi_mux_o1_0_phi_fu_5104_p4.read());
}

void snn_core_fc_last::thread_zext_ln88_fu_9113_p1() {
    zext_ln88_fu_9113_p1 = esl_zext<32,4>(max_idx_reg_5133_pp3_iter1_reg.read());
}

void snn_core_fc_last::thread_zext_ln90_fu_9042_p1() {
    zext_ln90_fu_9042_p1 = esl_zext<64,4>(ap_phi_mux_max_idx_phi_fu_5137_p4.read());
}

}

