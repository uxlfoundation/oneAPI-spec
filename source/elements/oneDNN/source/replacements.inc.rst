.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. namespace:: 0

.. |f16| replace:: :any:`f16 <dnnl::memory::data_type::f16>`
.. |bf16| replace:: :any:`bf16 <dnnl::memory::data_type::bf16>`
.. |f32| replace:: :any:`f32 <dnnl::memory::data_type::f32>`
.. |s32| replace:: :any:`s32 <dnnl::memory::data_type::s32>`
.. |s8| replace:: :any:`s8 <dnnl::memory::data_type::s8>`
.. |u8| replace:: :any:`u8 <dnnl::memory::data_type::u8>`

.. |_f16| replace:: :any:`dnnl::memory::data_type::f16`
.. |_bf16| replace:: :any:`dnnl::memory::data_type::bf16`
.. |_f32| replace:: :any:`dnnl::memory::data_type::f32`
.. |_s32| replace:: :any:`dnnl::memory::data_type::s32`
.. |_s8| replace:: :any:`dnnl::memory::data_type::s8`
.. |_u8| replace:: :any:`dnnl::memory::data_type::u8`

.. |any| replace:: :any:`any <dnnl::memory::format_tag::any>`
.. |abcdef| replace:: :any:`abcdef <dnnl::memory::format_tag::abcdef>`
.. |abcde| replace:: :any:`abcde <dnnl::memory::format_tag::abcde>`
.. |abcd| replace:: :any:`abcd <dnnl::memory::format_tag::abcd>`
.. |abdc| replace:: :any:`abdc <dnnl::memory::format_tag::abdc>`
.. |abc| replace:: :any:`abc <dnnl::memory::format_tag::abc>`
.. |ab| replace:: :any:`ab <dnnl::memory::format_tag::ab>`
.. |acb| replace:: :any:`acb <dnnl::memory::format_tag::acb>`
.. |acdb| replace:: :any:`acdb <dnnl::memory::format_tag::acdb>`
.. |acdeb| replace:: :any:`acdeb <dnnl::memory::format_tag::acdeb>`
.. |a| replace:: :any:`a <dnnl::memory::format_tag::a>`
.. |bac| replace:: :any:`bac <dnnl::memory::format_tag::bac>`
.. |ba| replace:: :any:`ba <dnnl::memory::format_tag::ba>`
.. |cba| replace:: :any:`cba <dnnl::memory::format_tag::cba>`
.. |cdba| replace:: :any:`cdba <dnnl::memory::format_tag::cdba>`
.. |cdeba| replace:: :any:`cdeba <dnnl::memory::format_tag::cdeba>`
.. |dcab| replace:: :any:`dcab <dnnl::memory::format_tag::dcab>`
.. |decab| replace:: :any:`decab <dnnl::memory::format_tag::decab>`
.. |defcab| replace:: :any:`defcab <dnnl::memory::format_tag::defcab>`
.. |dhwigo| replace:: :any:`dhwigo <dnnl::memory::format_tag::dhwigo>`
.. |dhwio| replace:: :any:`dhwio <dnnl::memory::format_tag::dhwio>`
.. |goidhw| replace:: :any:`goidhw <dnnl::memory::format_tag::goidhw>`
.. |goihw| replace:: :any:`goihw <dnnl::memory::format_tag::goihw>`
.. |goiw| replace:: :any:`goiw <dnnl::memory::format_tag::goiw>`
.. |hwigo| replace:: :any:`hwigo <dnnl::memory::format_tag::hwigo>`
.. |hwio| replace:: :any:`hwio <dnnl::memory::format_tag::hwio>`
.. |io| replace:: :any:`io <dnnl::memory::format_tag::io>`
.. |ldgoi| replace:: :any:`ldgoi <dnnl::memory::format_tag::ldgoi>`
.. |ldgo| replace:: :any:`ldgo <dnnl::memory::format_tag::ldgo>`
.. |ldigo| replace:: :any:`ldigo <dnnl::memory::format_tag::ldigo>`
.. |ldio| replace:: :any:`ldio <dnnl::memory::format_tag::ldio>`
.. |ldoi| replace:: :any:`ldoi <dnnl::memory::format_tag::ldoi>`
.. |ldnc| replace:: :any:`ldnc <dnnl::memory::format_tag::ldnc>`
.. |ncdhw| replace:: :any:`ncdhw <dnnl::memory::format_tag::ncdhw>`
.. |nchw| replace:: :any:`nchw <dnnl::memory::format_tag::nchw>`
.. |ncw| replace:: :any:`ncw <dnnl::memory::format_tag::ncw>`
.. |nc| replace:: :any:`nc <dnnl::memory::format_tag::nc>`
.. |ndhwc| replace:: :any:`ndhwc <dnnl::memory::format_tag::ndhwc>`
.. |nhwc| replace:: :any:`nhwc <dnnl::memory::format_tag::nhwc>`
.. |ntc| replace:: :any:`ntc <dnnl::memory::format_tag::ntc>`
.. |nt| replace:: :any:`nt <dnnl::memory::format_tag::nt>`
.. |nwc| replace:: :any:`nwc <dnnl::memory::format_tag::nwc>`
.. |oidhw| replace:: :any:`oidhw <dnnl::memory::format_tag::oidhw>`
.. |oihw| replace:: :any:`oihw <dnnl::memory::format_tag::oihw>`
.. |oiw| replace:: :any:`oiw <dnnl::memory::format_tag::oiw>`
.. |oi| replace:: :any:`oi <dnnl::memory::format_tag::oi>`
.. |tnc| replace:: :any:`tnc <dnnl::memory::format_tag::tnc>`
.. |tn| replace:: :any:`tn <dnnl::memory::format_tag::tn>`
.. |wigo| replace:: :any:`wigo <dnnl::memory::format_tag::wigo>`
.. |wio| replace:: :any:`wio <dnnl::memory::format_tag::wio>`
.. |x| replace:: :any:`x <dnnl::memory::format_tag::x>`

.. |_any| replace:: :any:`dnnl::memory::format_tag::any`
.. |_abcdef| replace:: :any:`dnnl::memory::format_tag::abcdef`
.. |_abcde| replace:: :any:`dnnl::memory::format_tag::abcde`
.. |_abcd| replace:: :any:`dnnl::memory::format_tag::abcd`
.. |_abc| replace:: :any:`dnnl::memory::format_tag::abc`
.. |_ab| replace:: :any:`dnnl::memory::format_tag::ab`
.. |_acb| replace:: :any:`dnnl::memory::format_tag::acb`
.. |_acdb| replace:: :any:`dnnl::memory::format_tag::acdb`
.. |_acdeb| replace:: :any:`dnnl::memory::format_tag::acdeb`
.. |_a| replace:: :any:`dnnl::memory::format_tag::a`
.. |_bac| replace:: :any:`dnnl::memory::format_tag::bac`
.. |_ba| replace:: :any:`dnnl::memory::format_tag::ba`
.. |_cba| replace:: :any:`dnnl::memory::format_tag::cba`
.. |_cdba| replace:: :any:`dnnl::memory::format_tag::cdba`
.. |_cdeba| replace:: :any:`dnnl::memory::format_tag::cdeba`
.. |_dcab| replace:: :any:`dnnl::memory::format_tag::dcab`
.. |_decab| replace:: :any:`dnnl::memory::format_tag::decab`
.. |_defcab| replace:: :any:`dnnl::memory::format_tag::defcab`
.. |_dhwigo| replace:: :any:`dnnl::memory::format_tag::dhwigo`
.. |_dhwio| replace:: :any:`dnnl::memory::format_tag::dhwio`
.. |_goidhw| replace:: :any:`dnnl::memory::format_tag::goidhw`
.. |_goihw| replace:: :any:`dnnl::memory::format_tag::goihw`
.. |_goiw| replace:: :any:`dnnl::memory::format_tag::goiw`
.. |_hwigo| replace:: :any:`dnnl::memory::format_tag::hwigo`
.. |_hwio| replace:: :any:`dnnl::memory::format_tag::hwio`
.. |_io| replace:: :any:`dnnl::memory::format_tag::io`
.. |_ldgoi| replace:: :any:`dnnl::memory::format_tag::ldgoi`
.. |_ldgo| replace:: :any:`dnnl::memory::format_tag::ldgo`
.. |_ldigo| replace:: :any:`dnnl::memory::format_tag::ldigo`
.. |_ldio| replace:: :any:`dnnl::memory::format_tag::ldio`
.. |_ldnc| replace:: :any:`dnnl::memory::format_tag::ldnc`
.. |_ncdhw| replace:: :any:`dnnl::memory::format_tag::ncdhw`
.. |_nchw| replace:: :any:`dnnl::memory::format_tag::nchw`
.. |_ncw| replace:: :any:`dnnl::memory::format_tag::ncw`
.. |_nc| replace:: :any:`dnnl::memory::format_tag::nc`
.. |_ndhwc| replace:: :any:`dnnl::memory::format_tag::ndhwc`
.. |_nhwc| replace:: :any:`dnnl::memory::format_tag::nhwc`
.. |_ntc| replace:: :any:`dnnl::memory::format_tag::ntc`
.. |_nt| replace:: :any:`dnnl::memory::format_tag::nt`
.. |_nwc| replace:: :any:`dnnl::memory::format_tag::nwc`
.. |_oidhw| replace:: :any:`dnnl::memory::format_tag::oidhw`
.. |_oihw| replace:: :any:`dnnl::memory::format_tag::oihw`
.. |_oiw| replace:: :any:`dnnl::memory::format_tag::oiw`
.. |_oi| replace:: :any:`dnnl::memory::format_tag::oi`
.. |_tnc| replace:: :any:`dnnl::memory::format_tag::tnc`
.. |_tn| replace:: :any:`dnnl::memory::format_tag::tn`
.. |_wigo| replace:: :any:`dnnl::memory::format_tag::wigo`
.. |_wio| replace:: :any:`dnnl::memory::format_tag::wio`
.. |_x| replace:: :any:`dnnl::memory::format_tag::x`

.. |normalization_flags_none| replace:: :any:`none <dnnl::normalization_flags::none>`
.. |use_global_stats| replace:: :any:`use_global_stats <dnnl::normalization_flags::use_global_stats>`
.. |use_scale| replace:: :any:`use_scale <dnnl::normalization_flags::use_scale>`
.. |use_shift| replace:: :any:`use_shift <dnnl::normalization_flags::use_shift>`
.. |fuse_norm_relu| replace:: :any:`fuse_norm_relu <dnnl::normalization_flags::fuse_norm_relu>`

.. |_normalization_flags_none| replace:: :any:`dnnl::normalization_flags::none`
.. |_use_global_stats| replace:: :any:`dnnl::normalization_flags::use_global_stats`
.. |_use_scaleshift| replace:: :any:`dnnl::normalization_flags::use_scaleshift`
.. |_fuse_norm_relu| replace:: :any:`dnnl::normalization_flags::fuse_norm_relu`

.. |backward| replace:: :any:`backward <dnnl::prop_kind::backward>`
.. |backward_data| replace:: :any:`backward_data <dnnl::prop_kind::backward_data>`
.. |forward_inference| replace:: :any:`forward_inference <dnnl::prop_kind::forward_inference>`
.. |forward_training| replace:: :any:`forward_training <dnnl::prop_kind::forward_training>`

.. |_backward| replace:: :any:`dnnl::prop_kind::backward`
.. |_backward_data| replace:: :any:`dnnl::prop_kind::backward_data`
.. |_forward_inference| replace:: :any:`dnnl::prop_kind::forward_inference`
.. |_forward_training| replace:: :any:`dnnl::prop_kind::forward_training`

.. |binary_add| replace:: :any:`binary_add <dnnl::algorithm::binary_add>`
.. |binary_max| replace:: :any:`binary_max <dnnl::algorithm::binary_max>`
.. |binary_min| replace:: :any:`binary_min <dnnl::algorithm::binary_min>`
.. |binary_mul| replace:: :any:`binary_mul <dnnl::algorithm::binary_mul>`
.. |convolution_auto| replace:: :any:`convolution_auto <dnnl::algorithm::convolution_auto>`
.. |convolution_direct| replace:: :any:`convolution_direct <dnnl::algorithm::convolution_direct>`
.. |convolution_winograd| replace:: :any:`convolution_winograd <dnnl::algorithm::convolution_winograd>`
.. |deconvolution_direct| replace:: :any:`deconvolution_direct <dnnl::algorithm::deconvolution_direct>`
.. |deconvolution_winograd| replace:: :any:`deconvolution_winograd <dnnl::algorithm::deconvolution_winograd>`
.. |eltwise_abs| replace:: :any:`eltwise_abs <dnnl::algorithm::eltwise_abs>`
.. |eltwise_bounded_relu| replace:: :any:`eltwise_bounded_relu <dnnl::algorithm::eltwise_bounded_relu>`
.. |eltwise_clip| replace:: :any:`eltwise_clip <dnnl::algorithm::eltwise_clip>`
.. |eltwise_clip_use_dst_for_bwd| replace:: :any:`eltwise_clip_use_dst_for_bwd <dnnl::algorithm::eltwise_clip_use_dst_for_bwd>`
.. |eltwise_elu_use_dst_for_bwd| replace:: :any:`eltwise_elu_use_dst_for_bwd <dnnl::algorithm::eltwise_elu_use_dst_for_bwd>`
.. |eltwise_elu| replace:: :any:`eltwise_elu <dnnl::algorithm::eltwise_elu>`
.. |eltwise_exp_use_dst_for_bwd| replace:: :any:`eltwise_exp_use_dst_for_bwd <dnnl::algorithm::eltwise_exp_use_dst_for_bwd>`
.. |eltwise_exp| replace:: :any:`eltwise_exp <dnnl::algorithm::eltwise_exp>`
.. |eltwise_gelu_erf| replace:: :any:`eltwise_gelu_erf <dnnl::algorithm::eltwise_gelu_erf>`
.. |eltwise_gelu_tanh| replace:: :any:`eltwise_gelu_tanh <dnnl::algorithm::eltwise_gelu_tanh>`
.. |eltwise_gelu| replace:: :any:`eltwise_gelu <dnnl::algorithm::eltwise_gelu>`
.. |eltwise_hardsigmoid| replace:: :any:`eltwise_hardsigmoid <dnnl::algorithm::eltwise_hardsigmoid>`
.. |eltwise_hardswish| replace:: :any:`eltwise_hardswish <dnnl::algorithm::eltwise_hardswish>`
.. |eltwise_linear| replace:: :any:`eltwise_linear <dnnl::algorithm::eltwise_linear>`
.. |eltwise_logistic_use_dst_for_bwd| replace:: :any:`eltwise_logistic_use_dst_for_bwd <dnnl::algorithm::eltwise_logistic_use_dst_for_bwd>`
.. |eltwise_logistic| replace:: :any:`eltwise_logistic <dnnl::algorithm::eltwise_logistic>`
.. |eltwise_log| replace:: :any:`eltwise_log <dnnl::algorithm::eltwise_log>`
.. |eltwise_mish| replace:: :any:`eltwise_mish <dnnl::algorithm::eltwise_mish>`
.. |eltwise_pow| replace:: :any:`eltwise_pow <dnnl::algorithm::eltwise_pow>`
.. |eltwise_relu_use_dst_for_bwd| replace:: :any:`eltwise_relu_use_dst_for_bwd <dnnl::algorithm::eltwise_relu_use_dst_for_bwd>`
.. |eltwise_relu| replace:: :any:`eltwise_relu <dnnl::algorithm::eltwise_relu>`
.. |eltwise_round| replace:: :any:`eltwise_round <dnnl::algorithm::eltwise_round>`
.. |eltwise_soft_relu| replace:: :any:`eltwise_soft_relu <dnnl::algorithm::eltwise_soft_relu>`
.. |eltwise_sqrt_use_dst_for_bwd| replace:: :any:`eltwise_sqrt_use_dst_for_bwd <dnnl::algorithm::eltwise_sqrt_use_dst_for_bwd>`
.. |eltwise_sqrt| replace:: :any:`eltwise_sqrt <dnnl::algorithm::eltwise_sqrt>`
.. |eltwise_square| replace:: :any:`eltwise_square <dnnl::algorithm::eltwise_square>`
.. |eltwise_swish| replace:: :any:`eltwise_swish <dnnl::algorithm::eltwise_swish>`
.. |eltwise_tanh_use_dst_for_bwd| replace:: :any:`eltwise_tanh_use_dst_for_bwd <dnnl::algorithm::eltwise_tanh_use_dst_for_bwd>`
.. |eltwise_tanh| replace:: :any:`eltwise_tanh <dnnl::algorithm::eltwise_tanh>`
.. |lbr_gru| replace:: :any:`lbr_gru <dnnl::algorithm::lbr_gru>`
.. |lrn_across_channels| replace:: :any:`lrn_across_channels <dnnl::algorithm::lrn_across_channels>`
.. |lrn_within_channel| replace:: :any:`lrn_within_channel <dnnl::algorithm::lrn_within_channel>`
.. |pooling_avg_exclude_padding| replace:: :any:`pooling_avg_exclude_padding <dnnl::algorithm::pooling_avg_exclude_padding>`
.. |pooling_avg_include_padding| replace:: :any:`pooling_avg_include_padding <dnnl::algorithm::pooling_avg_include_padding>`
.. |pooling_avg| replace:: :any:`pooling_avg <dnnl::algorithm::pooling_avg>`
.. |pooling_max| replace:: :any:`pooling_max <dnnl::algorithm::pooling_max>`
.. |resampling_linear| replace:: :any:`resampling_linear <dnnl::algorithm::resampling_linear>`
.. |resampling_nearest| replace:: :any:`resampling_nearest <dnnl::algorithm::resampling_nearest>`
.. |undef| replace:: :any:`undef <dnnl::algorithm::undef>`
.. |vanilla_gru| replace:: :any:`vanilla_gru <dnnl::algorithm::vanilla_gru>`
.. |vanilla_lstm| replace:: :any:`vanilla_lstm <dnnl::algorithm::vanilla_lstm>`
.. |vanilla_rnn| replace:: :any:`vanilla_rnn <dnnl::algorithm::vanilla_rnn>`

.. |_binary_add| replace:: :any:`dnnl::algorithm::binary_add`
.. |_binary_max| replace:: :any:`dnnl::algorithm::binary_max`
.. |_binary_min| replace:: :any:`dnnl::algorithm::binary_min`
.. |_binary_mul| replace:: :any:`dnnl::algorithm::binary_mul`
.. |_convolution_auto| replace:: :any:`dnnl::algorithm::convolution_auto`
.. |_convolution_direct| replace:: :any:`dnnl::algorithm::convolution_direct`
.. |_convolution_winograd| replace:: :any:`dnnl::algorithm::convolution_winograd`
.. |_deconvolution_direct| replace:: :any:`dnnl::algorithm::deconvolution_direct`
.. |_deconvolution_winograd| replace:: :any:`dnnl::algorithm::deconvolution_winograd`
.. |_eltwise_abs| replace:: :any:`dnnl::algorithm::eltwise_abs`
.. |_eltwise_bounded_relu| replace:: :any:`dnnl::algorithm::eltwise_bounded_relu`
.. |_eltwise_clip| replace:: :any:`dnnl::algorithm::eltwise_clip`
.. |_eltwise_elu_use_dst_for_bwd| replace:: :any:`dnnl::algorithm::eltwise_elu_use_dst_for_bwd`
.. |_eltwise_elu| replace:: :any:`dnnl::algorithm::eltwise_elu`
.. |_eltwise_exp_use_dst_for_bwd| replace:: :any:`dnnl::algorithm::eltwise_exp_use_dst_for_bwd`
.. |_eltwise_exp| replace:: :any:`dnnl::algorithm::eltwise_exp`
.. |_eltwise_gelu_erf| replace:: :any:`dnnl::algorithm::eltwise_gelu_erf`
.. |_eltwise_gelu_tanh| replace:: :any:`dnnl::algorithm::eltwise_gelu_tanh`
.. |_eltwise_gelu| replace:: :any:`dnnl::algorithm::eltwise_gelu`
.. |_eltwise_linear| replace:: :any:`dnnl::algorithm::eltwise_linear`
.. |_eltwise_logistic_use_dst_for_bwd| replace:: :any:`dnnl::algorithm::eltwise_logistic_use_dst_for_bwd`
.. |_eltwise_logistic| replace:: :any:`dnnl::algorithm::eltwise_logistic`
.. |_eltwise_log| replace:: :any:`dnnl::algorithm::eltwise_log`
.. |_eltwise_pow| replace:: :any:`dnnl::algorithm::eltwise_pow`
.. |_eltwise_relu_use_dst_for_bwd| replace:: :any:`dnnl::algorithm::eltwise_relu_use_dst_for_bwd`
.. |_eltwise_relu| replace:: :any:`dnnl::algorithm::eltwise_relu`
.. |_eltwise_round| replace:: :any:`dnnl::algorithm::eltwise_round`
.. |_eltwise_soft_relu| replace:: :any:`dnnl::algorithm::eltwise_soft_relu`
.. |_eltwise_sqrt_use_dst_for_bwd| replace:: :any:`dnnl::algorithm::eltwise_sqrt_use_dst_for_bwd`
.. |_eltwise_sqrt| replace:: :any:`dnnl::algorithm::eltwise_sqrt`
.. |_eltwise_square| replace:: :any:`dnnl::algorithm::eltwise_square`
.. |_eltwise_swish| replace:: :any:`dnnl::algorithm::eltwise_swish`
.. |_eltwise_tanh_use_dst_for_bwd| replace:: :any:`dnnl::algorithm::eltwise_tanh_use_dst_for_bwd`
.. |_eltwise_tanh| replace:: :any:`dnnl::algorithm::eltwise_tanh`
.. |_lbr_gru| replace:: :any:`dnnl::algorithm::lbr_gru`
.. |_lrn_across_channels| replace:: :any:`dnnl::algorithm::lrn_across_channels`
.. |_lrn_within_channel| replace:: :any:`dnnl::algorithm::lrn_within_channel`
.. |_pooling_avg_exclude_padding| replace:: :any:`dnnl::algorithm::pooling_avg_exclude_padding`
.. |_pooling_avg_include_padding| replace:: :any:`dnnl::algorithm::pooling_avg_include_padding`
.. |_pooling_avg| replace:: :any:`dnnl::algorithm::pooling_avg`
.. |_pooling_max| replace:: :any:`dnnl::algorithm::pooling_max`
.. |_resampling_linear| replace:: :any:`dnnl::algorithm::resampling_linear`
.. |_resampling_nearest| replace:: :any:`dnnl::algorithm::resampling_nearest`
.. |_undef| replace:: :any:`dnnl::algorithm::undef`
.. |_vanilla_gru| replace:: :any:`dnnl::algorithm::vanilla_gru`
.. |_vanilla_lstm| replace:: :any:`dnnl::algorithm::vanilla_lstm`
.. |_vanilla_rnn| replace:: :any:`dnnl::algorithm::vanilla_rnn`

.. |DNNL_ARG_ATTR_MULTIPLE_POST_OP| replace:: :c:macro:`DNNL_ARG_ATTR_MULTIPLE_POST_OP`
.. |DNNL_ARG_ATTR_MULTIPLE_POST_OP(po_index)| replace:: :c:macro:`DNNL_ARG_ATTR_MULTIPLE_POST_OP`
.. |DNNL_ARG_ATTR_SCALES| replace:: :c:macro:`DNNL_ARG_ATTR_SCALES`
.. |DNNL_ARG_ATTR_ZERO_POINTS| replace:: :c:macro:`DNNL_ARG_ATTR_ZERO_POINTS`
.. |DNNL_ARG_SRC_0| replace:: :c:macro:`DNNL_ARG_SRC_0`
.. |DNNL_ARG_SRC| replace:: :c:macro:`DNNL_ARG_SRC`
.. |DNNL_ARG_SRC_LAYER| replace:: :c:macro:`DNNL_ARG_SRC_LAYER`
.. |DNNL_ARG_FROM| replace:: :c:macro:`DNNL_ARG_FROM`
.. |DNNL_ARG_SRC_1| replace:: :c:macro:`DNNL_ARG_SRC_1`
.. |DNNL_ARG_SRC_ITER| replace:: :c:macro:`DNNL_ARG_SRC_ITER`
.. |DNNL_ARG_SRC_2| replace:: :c:macro:`DNNL_ARG_SRC_2`
.. |DNNL_ARG_SRC_ITER_C| replace:: :c:macro:`DNNL_ARG_SRC_ITER_C`
.. |DNNL_ARG_DST_0| replace:: :c:macro:`DNNL_ARG_DST_0`
.. |DNNL_ARG_DST| replace:: :c:macro:`DNNL_ARG_DST`
.. |DNNL_ARG_TO| replace:: :c:macro:`DNNL_ARG_TO`
.. |DNNL_ARG_DST_LAYER| replace:: :c:macro:`DNNL_ARG_DST_LAYER`
.. |DNNL_ARG_DST_1| replace:: :c:macro:`DNNL_ARG_DST_1`
.. |DNNL_ARG_DST_ITER| replace:: :c:macro:`DNNL_ARG_DST_ITER`
.. |DNNL_ARG_DST_2| replace:: :c:macro:`DNNL_ARG_DST_2`
.. |DNNL_ARG_DST_ITER_C| replace:: :c:macro:`DNNL_ARG_DST_ITER_C`
.. |DNNL_ARG_WEIGHTS_0| replace:: :c:macro:`DNNL_ARG_WEIGHTS_0`
.. |DNNL_ARG_WEIGHTS| replace:: :c:macro:`DNNL_ARG_WEIGHTS`
.. |DNNL_ARG_SCALE| replace:: :c:macro:`DNNL_ARG_SCALE`
.. |DNNL_ARG_SHIFT| replace:: :c:macro:`DNNL_ARG_SHIFT`
.. |DNNL_ARG_WEIGHTS_LAYER| replace:: :c:macro:`DNNL_ARG_WEIGHTS_LAYER`
.. |DNNL_ARG_WEIGHTS_1| replace:: :c:macro:`DNNL_ARG_WEIGHTS_1`
.. |DNNL_ARG_WEIGHTS_ITER| replace:: :c:macro:`DNNL_ARG_WEIGHTS_ITER`
.. |DNNL_ARG_WEIGHTS_PEEPHOLE| replace:: :c:macro:`DNNL_ARG_WEIGHTS_PEEPHOLE`
.. |DNNL_ARG_WEIGHTS_PROJECTION| replace:: :c:macro:`DNNL_ARG_WEIGHTS_PROJECTION`
.. |DNNL_ARG_BIAS| replace:: :c:macro:`DNNL_ARG_BIAS`
.. |DNNL_ARG_MEAN| replace:: :c:macro:`DNNL_ARG_MEAN`
.. |DNNL_ARG_VARIANCE| replace:: :c:macro:`DNNL_ARG_VARIANCE`
.. |DNNL_ARG_WORKSPACE| replace:: :c:macro:`DNNL_ARG_WORKSPACE`
.. |DNNL_ARG_SCRATCHPAD| replace:: :c:macro:`DNNL_ARG_SCRATCHPAD`
.. |DNNL_ARG_DIFF_SRC_0| replace:: :c:macro:`DNNL_ARG_DIFF_SRC_0`
.. |DNNL_ARG_DIFF_SRC| replace:: :c:macro:`DNNL_ARG_DIFF_SRC`
.. |DNNL_ARG_DIFF_SRC_LAYER| replace:: :c:macro:`DNNL_ARG_DIFF_SRC_LAYER`
.. |DNNL_ARG_DIFF_SRC_1| replace:: :c:macro:`DNNL_ARG_DIFF_SRC_1`
.. |DNNL_ARG_DIFF_SRC_ITER| replace:: :c:macro:`DNNL_ARG_DIFF_SRC_ITER`
.. |DNNL_ARG_DIFF_SRC_2| replace:: :c:macro:`DNNL_ARG_DIFF_SRC_2`
.. |DNNL_ARG_DIFF_SRC_ITER_C| replace:: :c:macro:`DNNL_ARG_DIFF_SRC_ITER_C`
.. |DNNL_ARG_DIFF_DST_0| replace:: :c:macro:`DNNL_ARG_DIFF_DST_0`
.. |DNNL_ARG_DIFF_DST| replace:: :c:macro:`DNNL_ARG_DIFF_DST`
.. |DNNL_ARG_DIFF_DST_LAYER| replace:: :c:macro:`DNNL_ARG_DIFF_DST_LAYER`
.. |DNNL_ARG_DIFF_DST_1| replace:: :c:macro:`DNNL_ARG_DIFF_DST_1`
.. |DNNL_ARG_DIFF_DST_ITER| replace:: :c:macro:`DNNL_ARG_DIFF_DST_ITER`
.. |DNNL_ARG_DIFF_DST_2| replace:: :c:macro:`DNNL_ARG_DIFF_DST_2`
.. |DNNL_ARG_DIFF_DST_ITER_C| replace:: :c:macro:`DNNL_ARG_DIFF_DST_ITER_C`
.. |DNNL_ARG_DIFF_WEIGHTS_0| replace:: :c:macro:`DNNL_ARG_DIFF_WEIGHTS_0`
.. |DNNL_ARG_DIFF_WEIGHTS| replace:: :c:macro:`DNNL_ARG_DIFF_WEIGHTS`
.. |DNNL_ARG_DIFF_SCALE| replace:: :c:macro:`DNNL_ARG_DIFF_SCALE`
.. |DNNL_ARG_DIFF_SHIFT| replace:: :c:macro:`DNNL_ARG_DIFF_SHIFT`
.. |DNNL_ARG_DIFF_WEIGHTS_LAYER| replace:: :c:macro:`DNNL_ARG_DIFF_WEIGHTS_LAYER`
.. |DNNL_ARG_DIFF_WEIGHTS_1| replace:: :c:macro:`DNNL_ARG_DIFF_WEIGHTS_1`
.. |DNNL_ARG_DIFF_WEIGHTS_ITER| replace:: :c:macro:`DNNL_ARG_DIFF_WEIGHTS_ITER`
.. |DNNL_ARG_DIFF_WEIGHTS_PEEPHOLE| replace:: :c:macro:`DNNL_ARG_DIFF_WEIGHTS_PEEPHOLE`
.. |DNNL_ARG_DIFF_WEIGHTS_PROJECTION| replace:: :c:macro:`DNNL_ARG_DIFF_WEIGHTS_PROJECTION`
.. |DNNL_ARG_DIFF_BIAS| replace:: :c:macro:`DNNL_ARG_DIFF_BIAS`
.. |DNNL_ARG_MULTIPLE_SRC| replace:: :c:macro:`DNNL_ARG_MULTIPLE_SRC`
.. |DNNL_ARG_MULTIPLE_DST| replace:: :c:macro:`DNNL_ARG_MULTIPLE_DST`
.. |DNNL_RUNTIME_DIM_VAL| replace:: :c:macro:`DNNL_RUNTIME_DIM_VAL`
.. |DNNL_RUNTIME_SIZE_VAL| replace:: :c:macro:`DNNL_RUNTIME_SIZE_VAL`
.. |DNNL_RUNTIME_F32_VAL| replace:: :c:macro:`DNNL_RUNTIME_F32_VAL`
.. |DNNL_RUNTIME_S32_VAL| replace:: :c:macro:`DNNL_RUNTIME_S32_VAL`

.. |algorithm::convolution_auto| replace:: :any:`dnnl::algorithm::convolution_auto`
.. |algorithm::convolution_direct| replace:: :any:`dnnl::algorithm::convolution_direct`
.. |algorithm::convolution_winograd| replace:: :any:`dnnl::algorithm::convolution_winograd`
.. |augru_backward::primitive_desc| replace:: :any:`dnnl::augru_backward::primitive_desc`
.. |augru_forward::primitive_desc| replace:: :any:`dnnl::augru_forward::primitive_desc`
.. |batch_normalization_forward::primitive_desc| replace:: :any:`dnnl::batch_normalization_forward::primitive_desc`
.. |concat| replace:: :any:`dnnl::concat`
.. |convolution_forward::primitive_desc| replace:: :any:`dnnl::convolution_forward::primitive_desc`
.. |convolution_forward| replace:: :any:`dnnl::convolution_forward`
.. |eltwise_backward::primitive_desc| replace:: :any:`dnnl::eltwise_backward::primitive_desc`
.. |eltwise_forward::primitive_desc| replace:: :any:`dnnl::eltwise_forward::primitive_desc`
.. |engine| replace:: :any:`dnnl::engine`
.. |error| replace:: :any:`dnnl::error`
.. |gru_backward::primitive_desc| replace:: :any:`dnnl::gru_backward::primitive_desc`
.. |gru_forward::primitive_desc| replace:: :any:`dnnl::gru_forward::primitive_desc`
.. |layer_normalization_forward::primitive_desc| replace:: :any:`dnnl::layer_normalization_forward::primtive_desc`
.. |lbr_augru_backward::primitive_desc| replace:: :any:`dnnl::lbr_augru_backward::primitive_desc`
.. |lbr_augru_forward::primitive_desc| replace:: :any:`dnnl::lbr_augru_forward::primitive_desc`
.. |lbr_gru_backward::primitive_desc| replace:: :any:`dnnl::lbr_gru_backward::primitive_desc`
.. |lbr_gru_forward::primitive_desc| replace:: :any:`dnnl::lbr_gru_forward::primitive_desc`
.. |lstm_backward::primitive_desc| replace:: :any:`dnnl::lstm_backward::primitive_desc`
.. |lstm_forward::primitive_desc| replace:: :any:`dnnl::lstm_forward::primitive_desc`
.. |memory::data_type::s32| replace:: :any:`dnnl::memory::data_type::s32`
.. |memory::desc::get_size| replace:: :any:`dnnl::memory::desc::get_size`
.. |memory::desc::permute_axes| replace:: :any:`dnnl::memory::desc::permute_axes`
.. |memory::desc::submemory_desc| replace:: :any:`dnnl::memory::desc::submemory_desc`
.. |memory::desc| replace:: :any:`dnnl::memory::desc`
.. |memory::format_tag::any| replace:: :any:`dnnl::memory::format_tag::any`
.. |memory::format_tag| replace:: :any:`dnnl::memory::format_tag`
.. |memory::get_data_handle| replace:: :any:`dnnl::memory::get_data_handle`
.. |memory::get_desc| replace:: :any:`dnnl::memory::get_desc`
.. |memory::get_engine| replace:: :any:`dnnl::memory::get_engine`
.. |memory::set_data_handle| replace:: :any:`dnnl::memory::set_data_handle`
.. |memory| replace:: :any:`dnnl::memory`
.. |pooling_forward::primitive_desc::workspace_desc| replace:: :any:`dnnl::pooling_forward::primitive_desc::workspace_desc`
.. |post_ops::append_eltwise| replace:: :any:`dnnl::post_ops::append_eltwise`
.. |post_ops::append_binary| replace:: :any:`dnnl::post_ops::append_binary`
.. |post_ops::append_sum| replace:: :any:`dnnl::post_ops::append_sum`
.. |post_ops::kind| replace:: :any:`dnnl::post_ops::kind`
.. |post_ops::len| replace:: :any:`dnnl::post_ops::len`
.. |post_ops| replace:: :any:`dnnl::post_ops`
.. |primimitive| replace:: :any:`dnnl::primimitive`
.. |primitive::execute| replace:: :any:`dnnl::primitive::execute`
.. |primitive::kind::eltwise| replace:: :any:`dnnl::primitive::kind::eltwise`
.. |primitive::kind::sum| replace:: :any:`dnnl::primitive::kind::sum`
.. |primitive_attr::set_fpmath_mode| replace:: :any:`dnnl::primitive_attr::set_fpmath_mode`
.. |primitive_attr::set_scales_mask| replace:: :any:`dnnl::primitive_attr::set_scales_mask`
.. |primitive_attr::set_zero_points_mask| replace:: :any:`dnnl::primitive_attr::set_zero_points_mask`
.. |primitive_attr::set_post_ops| replace:: :any:`dnnl::primitive_attr::set_post_ops`
.. |primitive_attr::set_scratchpad_mode| replace:: :any:`dnnl::primitive_attr::set_scratchpad_mode`

.. |primitive_desc::next_impl| replace:: :any:`dnnl::primitive_desc::next_impl`
.. |primitive_desc_base| replace:: :any:`dnnl::primitive_desc_base`
.. |primitive_desc| replace:: :any:`dnnl::primitive_desc`
.. |primitive| replace:: :any:`dnnl::primitive`
.. |reorder| replace:: :any:`dnnl::reorder`
.. |rnn_primitive_desc_base| replace:: :any:`dnnl::rnn_primitive_desc_base`
.. |scratchpad_mode::user| replace:: :any:`dnnl::scratchpad_mode::user`
.. |shuffle_forward::primitive_desc| replace:: :any:`dnnl::shuffle_forward::primitive_desc`
.. |stream::flags| replace:: :any:`dnnl::stream::flags`
.. |stream| replace:: :any:`dnnl::stream`
.. |sum| replace:: :any:`dnnl::sum`
.. |vanilla_rnn_backward::primitive_desc| replace:: :any:`dnnl::vanilla_rnn_backward::primitive_desc`
.. |vanilla_rnn_forward::primitive_desc| replace:: :any:`dnnl::vanilla_rnn_forward::primitive_desc`

.. |sycl_interop::get_buffer| replace:: :any:`dnnl::sycl_interop::get_buffer`
.. |sycl_interop::set_buffer| replace:: :any:`dnnl::sycl_interop::set_buffer`

.. |g_f32| replace:: :any:`f32<dnnl::graph::logical_tensor::data_type::f32>`
.. |g_u8| replace:: :any:`u8<dnnl::graph::logical_tensor::data_type::u8>`
.. |g_s8| replace:: :any:`s8<dnnl::graph::logical_tensor::data_type::s8>`
.. |g_bf16| replace:: :any:`bf16<dnnl::graph::logical_tensor::data_type::bf16>`
.. |g_f16| replace:: :any:`f16<dnnl::graph::logical_tensor::data_type::f16>`
.. |attr_auto_bcast| replace:: :any:`auto_broadcast<dnnl::graph::op::attr::auto_broadcast>`
.. |attr_alpha| replace:: :any:`alpha<dnnl::graph::op::attr::alpha>`
.. |attr_beta| replace:: :any:`beta<dnnl::graph::op::attr::beta>`
.. |attr_epsilon| replace:: :any:`epsilon<dnnl::graph::op::attr::epsilon>`
.. |attr_max| replace:: :any:`max<dnnl::graph::op::attr::max>`
.. |attr_min| replace:: :any:`min<dnnl::graph::op::attr::min>`
.. |attr_momentum| replace:: :any:`momentum<dnnl::graph::op::attr::momentum>`
.. |attr_scales| replace:: :any:`scales<dnnl::graph::op::attr::scales>`
.. |attr_axis| replace:: :any:`axis<dnnl::graph::op::attr::axis>`
.. |attr_begin_norm_axis| replace:: :any:`begin_norm_axis<dnnl::graph::op::attr::begin_norm_axis>`
.. |attr_groups| replace:: :any:`groups<dnnl::graph::op::attr::groups>`
.. |attr_axes| replace:: :any:`axes<dnnl::graph::op::attr::axes>`
.. |attr_dilations| replace:: :any:`dilations<dnnl::graph::op::attr::dilations>`
.. |attr_dst_shape| replace:: :any:`dst_shape<dnnl::graph::op::attr::dst_shape>`
.. |attr_kernel| replace:: :any:`kernel<dnnl::graph::op::attr::kernel>`
.. |attr_order| replace:: :any:`order<dnnl::graph::op::attr::order>`
.. |attr_output_padding| replace:: :any:`output_padding<dnnl::graph::op::attr::output_padding>`
.. |attr_pads_begin| replace:: :any:`pads_begin<dnnl::graph::op::attr::pads_begin>`
.. |attr_pads_end| replace:: :any:`pads_end<dnnl::graph::op::attr::pads_end>`
.. |attr_shape| replace:: :any:`shape<dnnl::graph::op::attr::shape>`
.. |attr_sizes| replace:: :any:`sizes<dnnl::graph::op::attr::sizes>`
.. |attr_src_shape| replace:: :any:`src_shape<dnnl::graph::op::attr::src_shape>`
.. |attr_strides| replace:: :any:`strides<dnnl::graph::op::attr::strides>`
.. |attr_weights_shape| replace:: :any:`weights_shape<dnnl::graph::op::attr::weights_shape>`
.. |attr_zps| replace:: :any:`zps<dnnl::graph::op::attr::zps>`
.. |attr_exclude_pad| replace:: :any:`exclude_pad<dnnl::graph::op::attr::exclude_pad>`
.. |attr_keep_dims| replace:: :any:`keep_dims<dnnl::graph::op::attr::keep_dims>`
.. |attr_keep_stats| replace:: :any:`keep_stats<dnnl::graph::op::attr::keep_stats>`
.. |attr_per_channel_broadcast| replace:: :any:`per_channel_broadcast<dnnl::graph::op::attr::per_channel_broadcast>`
.. |attr_special_zero| replace:: :any:`special_zero<dnnl::graph::op::attr::special_zero>`
.. |attr_transpose_a| replace:: :any:`transpose_a<dnnl::graph::op::attr::transpose_a>`
.. |attr_transpose_b| replace:: :any:`transpose_b<dnnl::graph::op::attr::transpose_b>`
.. |attr_use_affine| replace:: :any:`use_affine<dnnl::graph::op::attr::use_affine>`
.. |attr_use_dst| replace:: :any:`use_dst<dnnl::graph::op::attr::use_dst>`
.. |attr_auto_broadcast| replace:: :any:`auto_broadcast<dnnl::graph::op::attr::auto_broadcast>`
.. |attr_auto_pad| replace:: :any:`auto_pad<dnnl::graph::op::attr::auto_pad>`
.. |attr_coo_trmode| replace:: :any:`coordinate_transformation_mode<dnnl::graph::op::attr::coordinate_transformation_mode>`
.. |attr_data_format| replace:: :any:`data_format<dnnl::graph::op::attr::data_format>`
.. |attr_mode| replace:: :any:`mode<dnnl::graph::op::attr::mode>`
.. |attr_qtype| replace:: :any:`qtype<dnnl::graph::op::attr::qtype>`
.. |attr_rounding_type| replace:: :any:`rounding_type<dnnl::graph::op::attr::rounding_type>`
.. |attr_weights_format| replace:: :any:`weights_format<dnnl::graph::op::attr::weights_format>`
.. |layout_type| replace:: :any:`layout_type<dnnl::graph::logical_tensor::layout_type>`
.. |opaque| replace:: :any:`opaque<dnnl::graph::logical_tensor::layout_type::opaque>`
.. |strided| replace:: :any:`strided<dnnl::graph::logical_tensor::layout_type::strided>`
.. |quantize| replace:: :any:`quantize<dnnl::graph::op::kind::Quantize>`
.. |dequantize| replace:: :any:`dequantize<dnnl::graph::op::kind::Dequantize>`
.. |typecast| replace:: :any:`typecast<dnnl::graph::op::kind::TypeCast>`
.. |staticreshape| replace:: :any:`dnnl::graph::op::kind::StaticReshape`
.. |dynamicreshape| replace:: :any:`dnnl::graph::op::kind::DynamicReshape`
.. |graph| replace:: :any:`graph<dnnl::graph::graph>`
.. |partition| replace:: :any:`partition<dnnl::graph::partition>`
.. |compiled_partition| replace:: :any:`compiled_partition<dnnl::graph::compiled_partition>`
.. |finalize| replace:: :any:`dnnl::graph::graph::finalize`
.. |add_op| replace:: :any:`dnnl::graph::graph::add_op`
.. |get_partitions| replace:: :any:`dnnl::graph::graph::get_partitions`
.. |is_supported| replace:: :any:`dnnl::graph::partition::is_supported`
.. |DNNL_GRAPH_UNKNOWN_NDIMS| replace:: :c:macro:`DNNL_GRAPH_UNKNOWN_NDIMS`
.. |DNNL_GRAPH_UNKNOWN_DIM| replace:: :c:macro:`DNNL_GRAPH_UNKNOWN_DIM`
