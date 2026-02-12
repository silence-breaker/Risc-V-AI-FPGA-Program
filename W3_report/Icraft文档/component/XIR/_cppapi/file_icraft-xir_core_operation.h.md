# File operation.h



↰ [Parent directory](dir_icraft-xir_core.md#dir-icraft-xir-core) (`icraft-xir\core`)

<nav class="contents local" id="contents">

Contents

- [Definition (icraft-xir\core\operation.h)](#definition-icraft-xir-core-operation-h)

- [Includes](#includes)

- [Included By](#included-by)

- [Namespaces](#namespaces)

- [Classes](#classes)

- [Defines](#defines)

</nav>

## Definition (icraft-xir\core\operation.h)#

- [Program Listing for File operation.h](program_listing_file_icraft-xir_core_operation.h.md)

## Includes#

- icraft-utils/midware/path.hpp

- icraft-xir/base/map.h

- icraft-xir/base/string.h

- icraft-xir/core/attrs.h

- icraft-xir/core/compile_target.h

- icraft-xir/core/data.h

- map ([File map.h](file_icraft-xir_base_map.h.md#file-icraft-xir-base-map-h))

- set

## Included By#

- [File network.h](file_icraft-xir_core_network.h.md#file-icraft-xir-core-network-h)

- [File abs.h](file_icraft-xir_ops_abs.h.md#file-icraft-xir-ops-abs-h)

- [File acos.h](file_icraft-xir_ops_acos.h.md#file-icraft-xir-ops-acos-h)

- [File acosh.h](file_icraft-xir_ops_acosh.h.md#file-icraft-xir-ops-acosh-h)

- [File add.h](file_icraft-xir_ops_add.h.md#file-icraft-xir-ops-add-h)

- [File align_axis.h](file_icraft-xir_ops_align_axis.h.md#file-icraft-xir-ops-align-axis-h)

- [File argmax.h](file_icraft-xir_ops_argmax.h.md#file-icraft-xir-ops-argmax-h)

- [File argmin.h](file_icraft-xir_ops_argmin.h.md#file-icraft-xir-ops-argmin-h)

- [File asin.h](file_icraft-xir_ops_asin.h.md#file-icraft-xir-ops-asin-h)

- [File asinh.h](file_icraft-xir_ops_asinh.h.md#file-icraft-xir-ops-asinh-h)

- [File atan.h](file_icraft-xir_ops_atan.h.md#file-icraft-xir-ops-atan-h)

- [File atanh.h](file_icraft-xir_ops_atanh.h.md#file-icraft-xir-ops-atanh-h)

- [File avg_pool1d.h](file_icraft-xir_ops_avg_pool1d.h.md#file-icraft-xir-ops-avg-pool1d-h)

- [File avg_pool2d.h](file_icraft-xir_ops_avg_pool2d.h.md#file-icraft-xir-ops-avg-pool2d-h)

- [File avg_pool3d.h](file_icraft-xir_ops_avg_pool3d.h.md#file-icraft-xir-ops-avg-pool3d-h)

- [File batch_norm1d.h](file_icraft-xir_ops_batch_norm1d.h.md#file-icraft-xir-ops-batch-norm1d-h)

- [File batch_norm2d.h](file_icraft-xir_ops_batch_norm2d.h.md#file-icraft-xir-ops-batch-norm2d-h)

- [File batch_norm3d.h](file_icraft-xir_ops_batch_norm3d.h.md#file-icraft-xir-ops-batch-norm3d-h)

- [File cast.h](file_icraft-xir_ops_cast.h.md#file-icraft-xir-ops-cast-h)

- [File channel_shuffle.h](file_icraft-xir_ops_channel_shuffle.h.md#file-icraft-xir-ops-channel-shuffle-h)

- [File clamp_scalar.h](file_icraft-xir_ops_clamp_scalar.h.md#file-icraft-xir-ops-clamp-scalar-h)

- [File concat.h](file_icraft-xir_ops_concat.h.md#file-icraft-xir-ops-concat-h)

- [File conv1d.h](file_icraft-xir_ops_conv1d.h.md#file-icraft-xir-ops-conv1d-h)

- [File conv2d.h](file_icraft-xir_ops_conv2d.h.md#file-icraft-xir-ops-conv2d-h)

- [File conv3d.h](file_icraft-xir_ops_conv3d.h.md#file-icraft-xir-ops-conv3d-h)

- [File conv_transpose1d.h](file_icraft-xir_ops_conv_transpose1d.h.md#file-icraft-xir-ops-conv-transpose1d-h)

- [File conv_transpose2d.h](file_icraft-xir_ops_conv_transpose2d.h.md#file-icraft-xir-ops-conv-transpose2d-h)

- [File conv_transpose3d.h](file_icraft-xir_ops_conv_transpose3d.h.md#file-icraft-xir-ops-conv-transpose3d-h)

- [File copy.h](file_icraft-xir_ops_copy.h.md#file-icraft-xir-ops-copy-h)

- [File cos.h](file_icraft-xir_ops_cos.h.md#file-icraft-xir-ops-cos-h)

- [File cosh.h](file_icraft-xir_ops_cosh.h.md#file-icraft-xir-ops-cosh-h)

- [File div.h](file_icraft-xir_ops_div.h.md#file-icraft-xir-ops-div-h)

- [File divide_scalar.h](file_icraft-xir_ops_divide_scalar.h.md#file-icraft-xir-ops-divide-scalar-h)

- [File einsum.h](file_icraft-xir_ops_einsum.h.md#file-icraft-xir-ops-einsum-h)

- [File elu.h](file_icraft-xir_ops_elu.h.md#file-icraft-xir-ops-elu-h)

- [File equal.h](file_icraft-xir_ops_equal.h.md#file-icraft-xir-ops-equal-h)

- [File expand.h](file_icraft-xir_ops_expand.h.md#file-icraft-xir-ops-expand-h)

- [File gelu.h](file_icraft-xir_ops_gelu.h.md#file-icraft-xir-ops-gelu-h)

- [File greater.h](file_icraft-xir_ops_greater.h.md#file-icraft-xir-ops-greater-h)

- [File greater_equal.h](file_icraft-xir_ops_greater_equal.h.md#file-icraft-xir-ops-greater-equal-h)

- [File hard_op.h](file_icraft-xir_ops_hard_op.h.md#file-icraft-xir-ops-hard-op-h)

- [File hardshrink.h](file_icraft-xir_ops_hardshrink.h.md#file-icraft-xir-ops-hardshrink-h)

- [File hardsigmoid.h](file_icraft-xir_ops_hardsigmoid.h.md#file-icraft-xir-ops-hardsigmoid-h)

- [File hardswish.h](file_icraft-xir_ops_hardswish.h.md#file-icraft-xir-ops-hardswish-h)

- [File hardtanh.h](file_icraft-xir_ops_hardtanh.h.md#file-icraft-xir-ops-hardtanh-h)

- [File instance_norm1d.h](file_icraft-xir_ops_instance_norm1d.h.md#file-icraft-xir-ops-instance-norm1d-h)

- [File instance_norm2d.h](file_icraft-xir_ops_instance_norm2d.h.md#file-icraft-xir-ops-instance-norm2d-h)

- [File instance_norm3d.h](file_icraft-xir_ops_instance_norm3d.h.md#file-icraft-xir-ops-instance-norm3d-h)

- [File layer_norm.h](file_icraft-xir_ops_layer_norm.h.md#file-icraft-xir-ops-layer-norm-h)

- [File less.h](file_icraft-xir_ops_less.h.md#file-icraft-xir-ops-less-h)

- [File less_equal.h](file_icraft-xir_ops_less_equal.h.md#file-icraft-xir-ops-less-equal-h)

- [File log.h](file_icraft-xir_ops_log.h.md#file-icraft-xir-ops-log-h)

- [File log_sigmoid.h](file_icraft-xir_ops_log_sigmoid.h.md#file-icraft-xir-ops-log-sigmoid-h)

- [File log_softmax.h](file_icraft-xir_ops_log_softmax.h.md#file-icraft-xir-ops-log-softmax-h)

- [File matmul.h](file_icraft-xir_ops_matmul.h.md#file-icraft-xir-ops-matmul-h)

- [File max.h](file_icraft-xir_ops_max.h.md#file-icraft-xir-ops-max-h)

- [File max_pool1d.h](file_icraft-xir_ops_max_pool1d.h.md#file-icraft-xir-ops-max-pool1d-h)

- [File max_pool2d.h](file_icraft-xir_ops_max_pool2d.h.md#file-icraft-xir-ops-max-pool2d-h)

- [File max_pool3d.h](file_icraft-xir_ops_max_pool3d.h.md#file-icraft-xir-ops-max-pool3d-h)

- [File maximum.h](file_icraft-xir_ops_maximum.h.md#file-icraft-xir-ops-maximum-h)

- [File mean.h](file_icraft-xir_ops_mean.h.md#file-icraft-xir-ops-mean-h)

- [File min.h](file_icraft-xir_ops_min.h.md#file-icraft-xir-ops-min-h)

- [File minimum.h](file_icraft-xir_ops_minimum.h.md#file-icraft-xir-ops-minimum-h)

- [File mish.h](file_icraft-xir_ops_mish.h.md#file-icraft-xir-ops-mish-h)

- [File multiply.h](file_icraft-xir_ops_multiply.h.md#file-icraft-xir-ops-multiply-h)

- [File neg.h](file_icraft-xir_ops_neg.h.md#file-icraft-xir-ops-neg-h)

- [File normalize.h](file_icraft-xir_ops_normalize.h.md#file-icraft-xir-ops-normalize-h)

- [File not.h](file_icraft-xir_ops_not.h.md#file-icraft-xir-ops-not-h)

- [File not_equal.h](file_icraft-xir_ops_not_equal.h.md#file-icraft-xir-ops-not-equal-h)

- [File pad.h](file_icraft-xir_ops_pad.h.md#file-icraft-xir-ops-pad-h)

- [File pixel_shuffle.h](file_icraft-xir_ops_pixel_shuffle.h.md#file-icraft-xir-ops-pixel-shuffle-h)

- [File pow.h](file_icraft-xir_ops_pow.h.md#file-icraft-xir-ops-pow-h)

- [File prelu.h](file_icraft-xir_ops_prelu.h.md#file-icraft-xir-ops-prelu-h)

- [File prune_axis.h](file_icraft-xir_ops_prune_axis.h.md#file-icraft-xir-ops-prune-axis-h)

- [File relu.h](file_icraft-xir_ops_relu.h.md#file-icraft-xir-ops-relu-h)

- [File reshape.h](file_icraft-xir_ops_reshape.h.md#file-icraft-xir-ops-reshape-h)

- [File resize.h](file_icraft-xir_ops_resize.h.md#file-icraft-xir-ops-resize-h)

- [File roll.h](file_icraft-xir_ops_roll.h.md#file-icraft-xir-ops-roll-h)

- [File sigmoid.h](file_icraft-xir_ops_sigmoid.h.md#file-icraft-xir-ops-sigmoid-h)

- [File silu.h](file_icraft-xir_ops_silu.h.md#file-icraft-xir-ops-silu-h)

- [File sin.h](file_icraft-xir_ops_sin.h.md#file-icraft-xir-ops-sin-h)

- [File sinh.h](file_icraft-xir_ops_sinh.h.md#file-icraft-xir-ops-sinh-h)

- [File slice.h](file_icraft-xir_ops_slice.h.md#file-icraft-xir-ops-slice-h)

- [File softmax.h](file_icraft-xir_ops_softmax.h.md#file-icraft-xir-ops-softmax-h)

- [File softplus.h](file_icraft-xir_ops_softplus.h.md#file-icraft-xir-ops-softplus-h)

- [File softshrink.h](file_icraft-xir_ops_softshrink.h.md#file-icraft-xir-ops-softshrink-h)

- [File softsign.h](file_icraft-xir_ops_softsign.h.md#file-icraft-xir-ops-softsign-h)

- [File split.h](file_icraft-xir_ops_split.h.md#file-icraft-xir-ops-split-h)

- [File sqrt.h](file_icraft-xir_ops_sqrt.h.md#file-icraft-xir-ops-sqrt-h)

- [File squeeze.h](file_icraft-xir_ops_squeeze.h.md#file-icraft-xir-ops-squeeze-h)

- [File stack.h](file_icraft-xir_ops_stack.h.md#file-icraft-xir-ops-stack-h)

- [File sum.h](file_icraft-xir_ops_sum.h.md#file-icraft-xir-ops-sum-h)

- [File swap_order.h](file_icraft-xir_ops_swap_order.h.md#file-icraft-xir-ops-swap-order-h)

- [File tan.h](file_icraft-xir_ops_tan.h.md#file-icraft-xir-ops-tan-h)

- [File tanh.h](file_icraft-xir_ops_tanh.h.md#file-icraft-xir-ops-tanh-h)

- [File tanhshrink.h](file_icraft-xir_ops_tanhshrink.h.md#file-icraft-xir-ops-tanhshrink-h)

- [File tile.h](file_icraft-xir_ops_tile.h.md#file-icraft-xir-ops-tile-h)

- [File transpose.h](file_icraft-xir_ops_transpose.h.md#file-icraft-xir-ops-transpose-h)

- [File unfold.h](file_icraft-xir_ops_unfold.h.md#file-icraft-xir-ops-unfold-h)

- [File unknown.h](file_icraft-xir_ops_unknown.h.md#file-icraft-xir-ops-unknown-h)

- [File unstack.h](file_icraft-xir_ops_unstack.h.md#file-icraft-xir-ops-unstack-h)

- [File unsupport.h](file_icraft-xir_ops_unsupport.h.md#file-icraft-xir-ops-unsupport-h)

- [File upsample.h](file_icraft-xir_ops_upsample.h.md#file-icraft-xir-ops-upsample-h)

- [File where.h](file_icraft-xir_ops_where.h.md#file-icraft-xir-ops-where-h)

## Namespaces#

- [Namespace icraft](namespace_icraft.md#namespace-icraft)

- [Namespace icraft::xir](namespace_icraft__xir.md#namespace-icraft-xir)

## Classes#

- [Class Input](classicraft_1_1xir_1_1_input.md#exhale-class-classicraft-1-1xir-1-1-input)

- [Class InputNode](classicraft_1_1xir_1_1_input_node.md#exhale-class-classicraft-1-1xir-1-1-input-node)

- [Template Class IsActivate](classicraft_1_1xir_1_1_is_activate.md#exhale-class-classicraft-1-1xir-1-1-is-activate)

- [Template Class OpBase](classicraft_1_1xir_1_1_op_base.md#exhale-class-classicraft-1-1xir-1-1-op-base)

- [Class Operation](classicraft_1_1xir_1_1_operation.md#exhale-class-classicraft-1-1xir-1-1-operation)

- [Class OperationNode](classicraft_1_1xir_1_1_operation_node.md#exhale-class-classicraft-1-1xir-1-1-operation-node)

- [Template Class OpNodeBase](classicraft_1_1xir_1_1_op_node_base.md#exhale-class-classicraft-1-1xir-1-1-op-node-base)

- [Template Class OpTrait](classicraft_1_1xir_1_1_op_trait.md#exhale-class-classicraft-1-1xir-1-1-op-trait)

- [Class Output](classicraft_1_1xir_1_1_output.md#exhale-class-classicraft-1-1xir-1-1-output)

- [Class OutputNode](classicraft_1_1xir_1_1_output_node.md#exhale-class-classicraft-1-1xir-1-1-output-node)

## Defines#

- [Define ICRAFT_ATTR_FIELD](define_operation_8h_1a589fc08fd078a46929285ba7af07ec96.md#exhale-define-operation-8h-1a589fc08fd078a46929285ba7af07ec96)

- [Define ICRAFT_DECLARE_ATTRS](define_operation_8h_1a0587adc4fa59710015e27ce34a6d4f20.md#exhale-define-operation-8h-1a0587adc4fa59710015e27ce34a6d4f20)

- [Define ICRAFT_REGISTER_OP_NODE](define_operation_8h_1ad94829967e485c9a41f57ce3dc2dd69a.md#exhale-define-operation-8h-1ad94829967e485c9a41f57ce3dc2dd69a)

- [Define ICRAFT_REGISTER_TINFER](define_operation_8h_1ab6c5eefe51f60d0617b743d3bdf95b1f.md#exhale-define-operation-8h-1ab6c5eefe51f60d0617b743d3bdf95b1f)

                