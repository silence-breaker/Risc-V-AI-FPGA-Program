# Program Listing for File flatbuffers.h



↰ [Return to documentation for file](file_icraft-xir_serialize_flatbuffers.h.md#file-icraft-xir-serialize-flatbuffers-h) (`icraft-xir\serialize\flatbuffers.h`)


```cpp
#include <icraft-xir/base/dllexport.h>
#include <icraft-xir/core/network.h>
#include <icraft-xir/ops/ops.h>
#include "xir_generated.h"

flatbuffers::Offset<fbs::ACos> dumpACos(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ACos& object);

icraft::xir::ACos parseACos(const fbs::ACos* object);

flatbuffers::Offset<fbs::ACosh> dumpACosh(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ACosh& object);

icraft::xir::ACosh parseACosh(const fbs::ACosh* object);

flatbuffers::Offset<fbs::ASin> dumpASin(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ASin& object);

icraft::xir::ASin parseASin(const fbs::ASin* object);

flatbuffers::Offset<fbs::ASinh> dumpASinh(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ASinh& object);

icraft::xir::ASinh parseASinh(const fbs::ASinh* object);

flatbuffers::Offset<fbs::ATan> dumpATan(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ATan& object);

icraft::xir::ATan parseATan(const fbs::ATan* object);

flatbuffers::Offset<fbs::ATanh> dumpATanh(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ATanh& object);

icraft::xir::ATanh parseATanh(const fbs::ATanh* object);

flatbuffers::Offset<fbs::Abs> dumpAbs(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Abs& object);

icraft::xir::Abs parseAbs(const fbs::Abs* object);

flatbuffers::Offset<fbs::Add> dumpAdd(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Add& object);

icraft::xir::Add parseAdd(const fbs::Add* object);

flatbuffers::Offset<fbs::AlignAxis> dumpAlignAxis(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::AlignAxis& object);

icraft::xir::AlignAxis parseAlignAxis(const fbs::AlignAxis* object);

flatbuffers::Offset<fbs::AlignedUnit> dumpAlignedUnit(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::AlignedUnit& object);

icraft::xir::AlignedUnit parseAlignedUnit(const fbs::AlignedUnit* object);

flatbuffers::Offset<fbs::Argmax> dumpArgmax(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Argmax& object);

icraft::xir::Argmax parseArgmax(const fbs::Argmax* object);

flatbuffers::Offset<fbs::Argmin> dumpArgmin(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Argmin& object);

icraft::xir::Argmin parseArgmin(const fbs::Argmin* object);

flatbuffers::Offset<fbs::AvgPool1d> dumpAvgPool1d(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::AvgPool1d& object);

icraft::xir::AvgPool1d parseAvgPool1d(const fbs::AvgPool1d* object);

flatbuffers::Offset<fbs::AvgPool2d> dumpAvgPool2d(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::AvgPool2d& object);

icraft::xir::AvgPool2d parseAvgPool2d(const fbs::AvgPool2d* object);

flatbuffers::Offset<fbs::AvgPool3d> dumpAvgPool3d(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::AvgPool3d& object);

icraft::xir::AvgPool3d parseAvgPool3d(const fbs::AvgPool3d* object);

flatbuffers::Offset<fbs::AxisName> dumpAxisName(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::AxisName& object);

icraft::xir::AxisName parseAxisName(const fbs::AxisName* object);

uint8_t dumpAxisNameBoxType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::AxisName& object);

flatbuffers::Offset<void> dumpAxisNameBox(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::AxisName& object);

icraft::xir::AxisName parseAxisNameBox(uint8_t type, const void* object);

flatbuffers::Offset<fbs::AxisUnit> dumpAxisUnit(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::AxisUnit& object);

icraft::xir::AxisUnit parseAxisUnit(const fbs::AxisUnit* object);

flatbuffers::Offset<fbs::BaseQuantizedType> dumpBaseQuantizedType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::BaseQuantizedType& object);

icraft::xir::BaseQuantizedType parseBaseQuantizedType(const fbs::BaseQuantizedType* object);

uint8_t dumpBaseQuantizedTypeBoxType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::BaseQuantizedType& object);

flatbuffers::Offset<void> dumpBaseQuantizedTypeBox(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::BaseQuantizedType& object);

icraft::xir::BaseQuantizedType parseBaseQuantizedTypeBox(uint8_t type, const void* object);

flatbuffers::Offset<fbs::BatchNorm1d> dumpBatchNorm1d(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::BatchNorm1d& object);

icraft::xir::BatchNorm1d parseBatchNorm1d(const fbs::BatchNorm1d* object);

flatbuffers::Offset<fbs::BatchNorm2d> dumpBatchNorm2d(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::BatchNorm2d& object);

icraft::xir::BatchNorm2d parseBatchNorm2d(const fbs::BatchNorm2d* object);

flatbuffers::Offset<fbs::BatchNorm3d> dumpBatchNorm3d(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::BatchNorm3d& object);

icraft::xir::BatchNorm3d parseBatchNorm3d(const fbs::BatchNorm3d* object);

flatbuffers::Offset<fbs::Bool> dumpBool(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Bool& object);

icraft::xir::Bool parseBool(const fbs::Bool* object);

flatbuffers::Offset<fbs::BoolType> dumpBoolType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::BoolType& object);

icraft::xir::BoolType parseBoolType(const fbs::BoolType* object);

flatbuffers::Offset<fbs::BuyiTarget> dumpBuyiTarget(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::BuyiTarget& object);

icraft::xir::BuyiTarget parseBuyiTarget(const fbs::BuyiTarget* object);

flatbuffers::Offset<fbs::CalibratedType> dumpCalibratedType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::CalibratedType& object);

icraft::xir::CalibratedType parseCalibratedType(const fbs::CalibratedType* object);

flatbuffers::Offset<fbs::Cast> dumpCast(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Cast& object);

icraft::xir::Cast parseCast(const fbs::Cast* object);

flatbuffers::Offset<fbs::ChannelShuffle> dumpChannelShuffle(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ChannelShuffle& object);

icraft::xir::ChannelShuffle parseChannelShuffle(const fbs::ChannelShuffle* object);

flatbuffers::Offset<fbs::ChunkMem> dumpChunkMem(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ChunkMem& object);

icraft::xir::ChunkMem parseChunkMem(const fbs::ChunkMem* object);

flatbuffers::Offset<fbs::ClampScalar> dumpClampScalar(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ClampScalar& object);

icraft::xir::ClampScalar parseClampScalar(const fbs::ClampScalar* object);

flatbuffers::Offset<fbs::CompileTarget> dumpCompileTarget(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::CompileTarget& object);

icraft::xir::CompileTarget parseCompileTarget(const fbs::CompileTarget* object);

uint8_t dumpCompileTargetBoxType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::CompileTarget& object);

flatbuffers::Offset<void> dumpCompileTargetBox(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::CompileTarget& object);

icraft::xir::CompileTarget parseCompileTargetBox(uint8_t type, const void* object);

flatbuffers::Offset<fbs::Concat> dumpConcat(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Concat& object);

icraft::xir::Concat parseConcat(const fbs::Concat* object);

flatbuffers::Offset<fbs::Conv1d> dumpConv1d(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Conv1d& object);

icraft::xir::Conv1d parseConv1d(const fbs::Conv1d* object);

flatbuffers::Offset<fbs::Conv2d> dumpConv2d(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Conv2d& object);

icraft::xir::Conv2d parseConv2d(const fbs::Conv2d* object);

flatbuffers::Offset<fbs::Conv3d> dumpConv3d(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Conv3d& object);

icraft::xir::Conv3d parseConv3d(const fbs::Conv3d* object);

flatbuffers::Offset<fbs::ConvTranspose1d> dumpConvTranspose1d(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ConvTranspose1d& object);

icraft::xir::ConvTranspose1d parseConvTranspose1d(const fbs::ConvTranspose1d* object);

flatbuffers::Offset<fbs::ConvTranspose2d> dumpConvTranspose2d(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ConvTranspose2d& object);

icraft::xir::ConvTranspose2d parseConvTranspose2d(const fbs::ConvTranspose2d* object);

flatbuffers::Offset<fbs::ConvTranspose3d> dumpConvTranspose3d(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ConvTranspose3d& object);

icraft::xir::ConvTranspose3d parseConvTranspose3d(const fbs::ConvTranspose3d* object);

flatbuffers::Offset<fbs::Copy> dumpCopy(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Copy& object);

icraft::xir::Copy parseCopy(const fbs::Copy* object);

flatbuffers::Offset<fbs::Cos> dumpCos(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Cos& object);

icraft::xir::Cos parseCos(const fbs::Cos* object);

flatbuffers::Offset<fbs::Cosh> dumpCosh(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Cosh& object);

icraft::xir::Cosh parseCosh(const fbs::Cosh* object);

flatbuffers::Offset<fbs::CustomTarget> dumpCustomTarget(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::CustomTarget& object);

icraft::xir::CustomTarget parseCustomTarget(const fbs::CustomTarget* object);

flatbuffers::Offset<fbs::Data> dumpData(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Data& object);

icraft::xir::Data parseData(const fbs::Data* object);

uint8_t dumpDataBoxType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Data& object);

flatbuffers::Offset<void> dumpDataBox(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Data& object);

icraft::xir::Data parseDataBox(uint8_t type, const void* object);

flatbuffers::Offset<fbs::DataType> dumpDataType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::DataType& object);

icraft::xir::DataType parseDataType(const fbs::DataType* object);

uint8_t dumpDataTypeBoxType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::DataType& object);

flatbuffers::Offset<void> dumpDataTypeBox(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::DataType& object);

icraft::xir::DataType parseDataTypeBox(uint8_t type, const void* object);

flatbuffers::Offset<fbs::Div> dumpDiv(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Div& object);

icraft::xir::Div parseDiv(const fbs::Div* object);

flatbuffers::Offset<fbs::DivideScalar> dumpDivideScalar(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::DivideScalar& object);

icraft::xir::DivideScalar parseDivideScalar(const fbs::DivideScalar* object);

flatbuffers::Offset<fbs::ELU> dumpELU(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ELU& object);

icraft::xir::ELU parseELU(const fbs::ELU* object);

flatbuffers::Offset<fbs::Einsum> dumpEinsum(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Einsum& object);

icraft::xir::Einsum parseEinsum(const fbs::Einsum* object);

flatbuffers::Offset<fbs::Equal> dumpEqual(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Equal& object);

icraft::xir::Equal parseEqual(const fbs::Equal* object);

flatbuffers::Offset<fbs::ExpQuantizedScale> dumpExpQuantizedScale(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ExpQuantizedScale& object);

icraft::xir::ExpQuantizedScale parseExpQuantizedScale(const fbs::ExpQuantizedScale* object);

flatbuffers::Offset<fbs::ExpQuantizedScaleArray> dumpExpQuantizedScaleArray(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ExpQuantizedScaleArray& object);

icraft::xir::ExpQuantizedScaleArray parseExpQuantizedScaleArray(const fbs::ExpQuantizedScaleArray* object);

flatbuffers::Offset<fbs::Expand> dumpExpand(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Expand& object);

icraft::xir::Expand parseExpand(const fbs::Expand* object);

flatbuffers::Offset<fbs::ExternalMem> dumpExternalMem(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ExternalMem& object);

icraft::xir::ExternalMem parseExternalMem(const fbs::ExternalMem* object);

flatbuffers::Offset<fbs::FPGATarget> dumpFPGATarget(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::FPGATarget& object);

icraft::xir::FPGATarget parseFPGATarget(const fbs::FPGATarget* object);

flatbuffers::Offset<fbs::FloatImm> dumpFloatImm(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::FloatImm& object);

icraft::xir::FloatImm parseFloatImm(const fbs::FloatImm* object);

flatbuffers::Offset<fbs::FloatType> dumpFloatType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::FloatType& object);

icraft::xir::FloatType parseFloatType(const fbs::FloatType* object);

flatbuffers::Offset<fbs::GELU> dumpGELU(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::GELU& object);

icraft::xir::GELU parseGELU(const fbs::GELU* object);

flatbuffers::Offset<fbs::Greater> dumpGreater(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Greater& object);

icraft::xir::Greater parseGreater(const fbs::Greater* object);

flatbuffers::Offset<fbs::GreaterEqual> dumpGreaterEqual(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::GreaterEqual& object);

icraft::xir::GreaterEqual parseGreaterEqual(const fbs::GreaterEqual* object);

flatbuffers::Offset<fbs::HardOp> dumpHardOp(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::HardOp& object);

icraft::xir::HardOp parseHardOp(const fbs::HardOp* object);

flatbuffers::Offset<fbs::Hardshrink> dumpHardshrink(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Hardshrink& object);

icraft::xir::Hardshrink parseHardshrink(const fbs::Hardshrink* object);

flatbuffers::Offset<fbs::Hardsigmoid> dumpHardsigmoid(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Hardsigmoid& object);

icraft::xir::Hardsigmoid parseHardsigmoid(const fbs::Hardsigmoid* object);

flatbuffers::Offset<fbs::Hardswish> dumpHardswish(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Hardswish& object);

icraft::xir::Hardswish parseHardswish(const fbs::Hardswish* object);

flatbuffers::Offset<fbs::Hardtanh> dumpHardtanh(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Hardtanh& object);

icraft::xir::Hardtanh parseHardtanh(const fbs::Hardtanh* object);

flatbuffers::Offset<fbs::HostMem> dumpHostMem(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::HostMem& object);

icraft::xir::HostMem parseHostMem(const fbs::HostMem* object);

flatbuffers::Offset<fbs::HostTarget> dumpHostTarget(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::HostTarget& object);

icraft::xir::HostTarget parseHostTarget(const fbs::HostTarget* object);

flatbuffers::Offset<fbs::Input> dumpInput(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Input& object);

icraft::xir::Input parseInput(const fbs::Input* object);

flatbuffers::Offset<fbs::InstanceNorm1d> dumpInstanceNorm1d(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::InstanceNorm1d& object);

icraft::xir::InstanceNorm1d parseInstanceNorm1d(const fbs::InstanceNorm1d* object);

flatbuffers::Offset<fbs::InstanceNorm2d> dumpInstanceNorm2d(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::InstanceNorm2d& object);

icraft::xir::InstanceNorm2d parseInstanceNorm2d(const fbs::InstanceNorm2d* object);

flatbuffers::Offset<fbs::InstanceNorm3d> dumpInstanceNorm3d(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::InstanceNorm3d& object);

icraft::xir::InstanceNorm3d parseInstanceNorm3d(const fbs::InstanceNorm3d* object);

flatbuffers::Offset<fbs::IntImm> dumpIntImm(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::IntImm& object);

icraft::xir::IntImm parseIntImm(const fbs::IntImm* object);

flatbuffers::Offset<fbs::IntegerType> dumpIntegerType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::IntegerType& object);

icraft::xir::IntegerType parseIntegerType(const fbs::IntegerType* object);

flatbuffers::Offset<fbs::LayerNorm> dumpLayerNorm(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::LayerNorm& object);

icraft::xir::LayerNorm parseLayerNorm(const fbs::LayerNorm* object);

flatbuffers::Offset<fbs::Layout> dumpLayout(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Layout& object);

icraft::xir::Layout parseLayout(const fbs::Layout* object);

flatbuffers::Offset<fbs::Less> dumpLess(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Less& object);

icraft::xir::Less parseLess(const fbs::Less* object);

flatbuffers::Offset<fbs::LessEqual> dumpLessEqual(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::LessEqual& object);

icraft::xir::LessEqual parseLessEqual(const fbs::LessEqual* object);

flatbuffers::Offset<fbs::Log> dumpLog(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Log& object);

icraft::xir::Log parseLog(const fbs::Log* object);

flatbuffers::Offset<fbs::LogSigmoid> dumpLogSigmoid(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::LogSigmoid& object);

icraft::xir::LogSigmoid parseLogSigmoid(const fbs::LogSigmoid* object);

flatbuffers::Offset<fbs::LogSoftmax> dumpLogSoftmax(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::LogSoftmax& object);

icraft::xir::LogSoftmax parseLogSoftmax(const fbs::LogSoftmax* object);

flatbuffers::Offset<fbs::Matmul> dumpMatmul(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Matmul& object);

icraft::xir::Matmul parseMatmul(const fbs::Matmul* object);

flatbuffers::Offset<fbs::Max> dumpMax(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Max& object);

icraft::xir::Max parseMax(const fbs::Max* object);

flatbuffers::Offset<fbs::MaxPool1d> dumpMaxPool1d(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::MaxPool1d& object);

icraft::xir::MaxPool1d parseMaxPool1d(const fbs::MaxPool1d* object);

flatbuffers::Offset<fbs::MaxPool2d> dumpMaxPool2d(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::MaxPool2d& object);

icraft::xir::MaxPool2d parseMaxPool2d(const fbs::MaxPool2d* object);

flatbuffers::Offset<fbs::MaxPool3d> dumpMaxPool3d(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::MaxPool3d& object);

icraft::xir::MaxPool3d parseMaxPool3d(const fbs::MaxPool3d* object);

flatbuffers::Offset<fbs::Maximum> dumpMaximum(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Maximum& object);

icraft::xir::Maximum parseMaximum(const fbs::Maximum* object);

flatbuffers::Offset<fbs::Mean> dumpMean(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Mean& object);

icraft::xir::Mean parseMean(const fbs::Mean* object);

flatbuffers::Offset<fbs::MemType> dumpMemType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::MemType& object);

icraft::xir::MemType parseMemType(const fbs::MemType* object);

uint8_t dumpMemTypeBoxType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::MemType& object);

flatbuffers::Offset<void> dumpMemTypeBox(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::MemType& object);

icraft::xir::MemType parseMemTypeBox(uint8_t type, const void* object);

flatbuffers::Offset<fbs::MergedAxisDistr> dumpMergedAxisDistr(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::MergedAxisDistr& object);

icraft::xir::MergedAxisDistr parseMergedAxisDistr(const fbs::MergedAxisDistr* object);

flatbuffers::Offset<fbs::Min> dumpMin(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Min& object);

icraft::xir::Min parseMin(const fbs::Min* object);

flatbuffers::Offset<fbs::Minimum> dumpMinimum(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Minimum& object);

icraft::xir::Minimum parseMinimum(const fbs::Minimum* object);

flatbuffers::Offset<fbs::Mish> dumpMish(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Mish& object);

icraft::xir::Mish parseMish(const fbs::Mish* object);

flatbuffers::Offset<fbs::Multiply> dumpMultiply(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Multiply& object);

icraft::xir::Multiply parseMultiply(const fbs::Multiply* object);

flatbuffers::Offset<fbs::Neg> dumpNeg(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Neg& object);

icraft::xir::Neg parseNeg(const fbs::Neg* object);

flatbuffers::Offset<fbs::Network> dumpNetwork(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Network& object);

icraft::xir::Network parseNetwork(const fbs::Network* object);

flatbuffers::Offset<fbs::NetworkBase> dumpNetworkBase(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::NetworkBase& object);

icraft::xir::NetworkBase parseNetworkBase(const fbs::NetworkBase* object);

uint8_t dumpNetworkBaseBoxType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::NetworkBase& object);

flatbuffers::Offset<void> dumpNetworkBaseBox(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::NetworkBase& object);

icraft::xir::NetworkBase parseNetworkBaseBox(uint8_t type, const void* object);

flatbuffers::Offset<fbs::Normalize> dumpNormalize(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Normalize& object);

icraft::xir::Normalize parseNormalize(const fbs::Normalize* object);

flatbuffers::Offset<fbs::NormalizedQuantizedType> dumpNormalizedQuantizedType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::NormalizedQuantizedType& object);

icraft::xir::NormalizedQuantizedType parseNormalizedQuantizedType(const fbs::NormalizedQuantizedType* object);

flatbuffers::Offset<fbs::NormalizedType> dumpNormalizedType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::NormalizedType& object);

icraft::xir::NormalizedType parseNormalizedType(const fbs::NormalizedType* object);

flatbuffers::Offset<fbs::NormratioArray> dumpNormratioArray(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::NormratioArray& object);

icraft::xir::NormratioArray parseNormratioArray(const fbs::NormratioArray* object);

flatbuffers::Offset<fbs::Not> dumpNot(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Not& object);

icraft::xir::Not parseNot(const fbs::Not* object);

flatbuffers::Offset<fbs::NotEqual> dumpNotEqual(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::NotEqual& object);

icraft::xir::NotEqual parseNotEqual(const fbs::NotEqual* object);

flatbuffers::Offset<fbs::ObjectRef> dumpObjectRef(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ObjectRef& object);

icraft::xir::ObjectRef parseObjectRef(const fbs::ObjectRef* object);

uint8_t dumpObjectRefBoxType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ObjectRef& object);

flatbuffers::Offset<void> dumpObjectRefBox(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ObjectRef& object);

icraft::xir::ObjectRef parseObjectRefBox(uint8_t type, const void* object);

flatbuffers::Offset<fbs::OnChipMem> dumpOnChipMem(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::OnChipMem& object);

icraft::xir::OnChipMem parseOnChipMem(const fbs::OnChipMem* object);

flatbuffers::Offset<fbs::Operation> dumpOperation(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Operation& object);

icraft::xir::Operation parseOperation(const fbs::Operation* object);

uint8_t dumpOperationBoxType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Operation& object);

flatbuffers::Offset<void> dumpOperationBox(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Operation& object);

icraft::xir::Operation parseOperationBox(uint8_t type, const void* object);

flatbuffers::Offset<fbs::Output> dumpOutput(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Output& object);

icraft::xir::Output parseOutput(const fbs::Output* object);

flatbuffers::Offset<fbs::PReLU> dumpPReLU(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::PReLU& object);

icraft::xir::PReLU parsePReLU(const fbs::PReLU* object);

flatbuffers::Offset<fbs::Pad> dumpPad(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Pad& object);

icraft::xir::Pad parsePad(const fbs::Pad* object);

flatbuffers::Offset<fbs::Params> dumpParams(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Params& object);

icraft::xir::Params parseParams(const fbs::Params* object);

flatbuffers::Offset<fbs::PixelShuffle> dumpPixelShuffle(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::PixelShuffle& object);

icraft::xir::PixelShuffle parsePixelShuffle(const fbs::PixelShuffle* object);

flatbuffers::Offset<fbs::Pow> dumpPow(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Pow& object);

icraft::xir::Pow parsePow(const fbs::Pow* object);

flatbuffers::Offset<fbs::PruneAxis> dumpPruneAxis(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::PruneAxis& object);

icraft::xir::PruneAxis parsePruneAxis(const fbs::PruneAxis* object);

flatbuffers::Offset<fbs::QuantizedScale> dumpQuantizedScale(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::QuantizedScale& object);

icraft::xir::QuantizedScale parseQuantizedScale(const fbs::QuantizedScale* object);

uint8_t dumpQuantizedScaleBoxType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::QuantizedScale& object);

flatbuffers::Offset<void> dumpQuantizedScaleBox(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::QuantizedScale& object);

icraft::xir::QuantizedScale parseQuantizedScaleBox(uint8_t type, const void* object);

flatbuffers::Offset<fbs::QuantizedScaleArray> dumpQuantizedScaleArray(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::QuantizedScaleArray& object);

icraft::xir::QuantizedScaleArray parseQuantizedScaleArray(const fbs::QuantizedScaleArray* object);

uint8_t dumpQuantizedScaleArrayBoxType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::QuantizedScaleArray& object);

flatbuffers::Offset<void> dumpQuantizedScaleArrayBox(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::QuantizedScaleArray& object);

icraft::xir::QuantizedScaleArray parseQuantizedScaleArrayBox(uint8_t type, const void* object);

flatbuffers::Offset<fbs::QuantizedType> dumpQuantizedType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::QuantizedType& object);

icraft::xir::QuantizedType parseQuantizedType(const fbs::QuantizedType* object);

uint8_t dumpQuantizedTypeBoxType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::QuantizedType& object);

flatbuffers::Offset<void> dumpQuantizedTypeBox(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::QuantizedType& object);

icraft::xir::QuantizedType parseQuantizedTypeBox(uint8_t type, const void* object);

flatbuffers::Offset<fbs::ReLU> dumpReLU(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ReLU& object);

icraft::xir::ReLU parseReLU(const fbs::ReLU* object);

flatbuffers::Offset<fbs::Reshape> dumpReshape(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Reshape& object);

icraft::xir::Reshape parseReshape(const fbs::Reshape* object);

flatbuffers::Offset<fbs::Resize> dumpResize(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Resize& object);

icraft::xir::Resize parseResize(const fbs::Resize* object);

flatbuffers::Offset<fbs::Roll> dumpRoll(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Roll& object);

icraft::xir::Roll parseRoll(const fbs::Roll* object);

flatbuffers::Offset<fbs::ScalarImm> dumpScalarImm(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ScalarImm& object);

icraft::xir::ScalarImm parseScalarImm(const fbs::ScalarImm* object);

uint8_t dumpScalarImmBoxType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ScalarImm& object);

flatbuffers::Offset<void> dumpScalarImmBox(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ScalarImm& object);

icraft::xir::ScalarImm parseScalarImmBox(uint8_t type, const void* object);

flatbuffers::Offset<fbs::ScalarType> dumpScalarType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ScalarType& object);

icraft::xir::ScalarType parseScalarType(const fbs::ScalarType* object);

uint8_t dumpScalarTypeBoxType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ScalarType& object);

flatbuffers::Offset<void> dumpScalarTypeBox(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ScalarType& object);

icraft::xir::ScalarType parseScalarTypeBox(uint8_t type, const void* object);

flatbuffers::Offset<fbs::SiLU> dumpSiLU(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::SiLU& object);

icraft::xir::SiLU parseSiLU(const fbs::SiLU* object);

flatbuffers::Offset<fbs::Sigmoid> dumpSigmoid(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Sigmoid& object);

icraft::xir::Sigmoid parseSigmoid(const fbs::Sigmoid* object);

flatbuffers::Offset<fbs::Sin> dumpSin(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Sin& object);

icraft::xir::Sin parseSin(const fbs::Sin* object);

flatbuffers::Offset<fbs::Sinh> dumpSinh(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Sinh& object);

icraft::xir::Sinh parseSinh(const fbs::Sinh* object);

flatbuffers::Offset<fbs::Slice> dumpSlice(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Slice& object);

icraft::xir::Slice parseSlice(const fbs::Slice* object);

flatbuffers::Offset<fbs::Softmax> dumpSoftmax(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Softmax& object);

icraft::xir::Softmax parseSoftmax(const fbs::Softmax* object);

flatbuffers::Offset<fbs::Softplus> dumpSoftplus(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Softplus& object);

icraft::xir::Softplus parseSoftplus(const fbs::Softplus* object);

flatbuffers::Offset<fbs::Softshrink> dumpSoftshrink(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Softshrink& object);

icraft::xir::Softshrink parseSoftshrink(const fbs::Softshrink* object);

flatbuffers::Offset<fbs::Softsign> dumpSoftsign(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Softsign& object);

icraft::xir::Softsign parseSoftsign(const fbs::Softsign* object);

flatbuffers::Offset<fbs::Split> dumpSplit(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Split& object);

icraft::xir::Split parseSplit(const fbs::Split* object);

flatbuffers::Offset<fbs::Sqrt> dumpSqrt(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Sqrt& object);

icraft::xir::Sqrt parseSqrt(const fbs::Sqrt* object);

flatbuffers::Offset<fbs::Squeeze> dumpSqueeze(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Squeeze& object);

icraft::xir::Squeeze parseSqueeze(const fbs::Squeeze* object);

flatbuffers::Offset<fbs::Stack> dumpStack(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Stack& object);

icraft::xir::Stack parseStack(const fbs::Stack* object);

flatbuffers::Offset<fbs::Sum> dumpSum(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Sum& object);

icraft::xir::Sum parseSum(const fbs::Sum* object);

flatbuffers::Offset<fbs::SwapOrder> dumpSwapOrder(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::SwapOrder& object);

icraft::xir::SwapOrder parseSwapOrder(const fbs::SwapOrder* object);

flatbuffers::Offset<fbs::Tan> dumpTan(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Tan& object);

icraft::xir::Tan parseTan(const fbs::Tan* object);

flatbuffers::Offset<fbs::Tanh> dumpTanh(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Tanh& object);

icraft::xir::Tanh parseTanh(const fbs::Tanh* object);

flatbuffers::Offset<fbs::Tanhshrink> dumpTanhshrink(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Tanhshrink& object);

icraft::xir::Tanhshrink parseTanhshrink(const fbs::Tanhshrink* object);

flatbuffers::Offset<fbs::TensorType> dumpTensorType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::TensorType& object);

icraft::xir::TensorType parseTensorType(const fbs::TensorType* object);

flatbuffers::Offset<fbs::Tile> dumpTile(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Tile& object);

icraft::xir::Tile parseTile(const fbs::Tile* object);

flatbuffers::Offset<fbs::Transpose> dumpTranspose(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Transpose& object);

icraft::xir::Transpose parseTranspose(const fbs::Transpose* object);

flatbuffers::Offset<fbs::Unfold> dumpUnfold(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Unfold& object);

icraft::xir::Unfold parseUnfold(const fbs::Unfold* object);

flatbuffers::Offset<fbs::Unknown> dumpUnknown(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Unknown& object);

icraft::xir::Operation parseUnknown(const fbs::Unknown* object);

flatbuffers::Offset<fbs::Unstack> dumpUnstack(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Unstack& object);

icraft::xir::Unstack parseUnstack(const fbs::Unstack* object);

flatbuffers::Offset<fbs::Unsupport> dumpUnsupport(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Unsupport& object);

icraft::xir::Unsupport parseUnsupport(const fbs::Unsupport* object);

flatbuffers::Offset<fbs::Upsample> dumpUpsample(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Upsample& object);

icraft::xir::Upsample parseUpsample(const fbs::Upsample* object);

flatbuffers::Offset<fbs::Value> dumpValue(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Value& object);

icraft::xir::Value parseValue(const fbs::Value* object);

uint8_t dumpValueBoxType(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Value& object);

flatbuffers::Offset<void> dumpValueBox(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Value& object);

icraft::xir::Value parseValueBox(uint8_t type, const void* object);

flatbuffers::Offset<fbs::Where> dumpWhere(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::Where& object);

icraft::xir::Where parseWhere(const fbs::Where* object);

flatbuffers::Offset<fbs::WolongTarget> dumpWolongTarget(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::WolongTarget& object);

icraft::xir::WolongTarget parseWolongTarget(const fbs::WolongTarget* object);

flatbuffers::Offset<fbs::ZhugeTarget> dumpZhugeTarget(flatbuffers::FlatBufferBuilder& builder, const icraft::xir::ZhugeTarget& object);

icraft::xir::ZhugeTarget parseZhugeTarget(const fbs::ZhugeTarget* object);

struct BufferData {
    uint8_t* buffer = NULL;
    int size = 0;
    void *impl;
};

extern "C" {
    XIR_DLL BufferData toFlatBuffers(const icraft::xir::Network& object);

    //XIR_DLL void freeBuffer(uint8_t* buffer);
    XIR_DLL void freeBuffer(BufferData* buffer);

    XIR_DLL icraft::xir::Network fromFlatBuffers(char* map_addr, uint64_t byte_size);
}
</pre>
```
