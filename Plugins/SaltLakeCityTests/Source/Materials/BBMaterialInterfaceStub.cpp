// SaltLakeCity 4.26

#include "BBMaterialInterfaceStub.h"

UBBMaterialInterfaceStub::UBBMaterialInterfaceStub() :
	Super()
{
}

UMaterial * UBBMaterialInterfaceStub::GetMaterial()
{
	return nullptr;
}

const UMaterial * UBBMaterialInterfaceStub::GetMaterial() const
{
	return nullptr;
}

const UMaterial * UBBMaterialInterfaceStub::GetMaterial_Concurrent(TMicRecursionGuard RecursionGuard) const
{
	return nullptr;
}

UPhysicalMaterial * UBBMaterialInterfaceStub::GetPhysicalMaterial() const
{
	return nullptr;
}

UPhysicalMaterialMask * UBBMaterialInterfaceStub::GetPhysicalMaterialMask() const
{
	return nullptr;
}

UPhysicalMaterial * UBBMaterialInterfaceStub::GetPhysicalMaterialFromMap(int32 Index) const
{
	return nullptr;
}

void UBBMaterialInterfaceStub::GetUsedTextures(TArray<UTexture*>& OutTextures, EMaterialQualityLevel::Type QualityLevel, bool bAllQualityLevels, ERHIFeatureLevel::Type FeatureLevel, bool bAllFeatureLevels) const
{
	OutTextures.Empty();
}

void UBBMaterialInterfaceStub::OverrideTexture(const UTexture * InTextureToOverride, UTexture * OverrideTexture, ERHIFeatureLevel::Type InFeatureLevel)
{
}

void UBBMaterialInterfaceStub::OverrideVectorParameterDefault(const FHashedMaterialParameterInfo & ParameterInfo, const FLinearColor & Value, bool bOverride, ERHIFeatureLevel::Type FeatureLevel)
{
}

void UBBMaterialInterfaceStub::OverrideScalarParameterDefault(const FHashedMaterialParameterInfo & ParameterInfo, float Value, bool bOverride, ERHIFeatureLevel::Type FeatureLevel)
{
}

bool UBBMaterialInterfaceStub::CheckMaterialUsage(const EMaterialUsage Usage)
{
	return false;
}

bool UBBMaterialInterfaceStub::CheckMaterialUsage_Concurrent(const EMaterialUsage Usage) const
{
	return false;
}

bool UBBMaterialInterfaceStub::GetStaticSwitchParameterValues(FStaticParamEvaluationContext & EvalContext, TBitArray<>& OutValues, FGuid * OutExpressionGuids, bool bCheckParent) const
{
	return false;
}

bool UBBMaterialInterfaceStub::GetStaticComponentMaskParameterValues(FStaticParamEvaluationContext & EvalContext, TBitArray<>& OutRGBAOrderedValues, FGuid * OutExpressionGuids, bool bCheckParent) const
{
	return false;
}

bool UBBMaterialInterfaceStub::GetMaterialLayersParameterValue(const FHashedMaterialParameterInfo & ParameterInfo, FMaterialLayersFunctions & OutLayers, FGuid & OutExpressionGuid, bool bCheckParent) const
{
	return false;
}

bool UBBMaterialInterfaceStub::GetTerrainLayerWeightParameterValue(const FHashedMaterialParameterInfo & ParameterInfo, int32 & OutWeightmapIndex, FGuid & OutExpressionGuid) const
{
	return false;
}

bool UBBMaterialInterfaceStub::GetParameterSortPriority(const FHashedMaterialParameterInfo & ParameterInfo, int32 & OutSortPriority, const TArray<struct FStaticMaterialLayersParameter>* MaterialLayersParameters) const
{
	return false;
}

bool UBBMaterialInterfaceStub::GetGroupSortPriority(const FString & InGroupName, int32 & OutSortPriority) const
{
	return false;
}

void UBBMaterialInterfaceStub::GetAllScalarParameterInfo(TArray<FMaterialParameterInfo>& OutParameterInfo, TArray<FGuid>& OutParameterIds) const
{
	OutParameterInfo.Empty();
}

void UBBMaterialInterfaceStub::GetAllVectorParameterInfo(TArray<FMaterialParameterInfo>& OutParameterInfo, TArray<FGuid>& OutParameterIds) const
{
	OutParameterInfo.Empty();
}

void UBBMaterialInterfaceStub::GetAllTextureParameterInfo(TArray<FMaterialParameterInfo>& OutParameterInfo, TArray<FGuid>& OutParameterIds) const
{
	OutParameterInfo.Empty();
}

void UBBMaterialInterfaceStub::GetAllRuntimeVirtualTextureParameterInfo(TArray<FMaterialParameterInfo>& OutParameterInfo, TArray<FGuid>& OutParameterIds) const
{
	OutParameterInfo.Empty();
}

void UBBMaterialInterfaceStub::GetAllFontParameterInfo(TArray<FMaterialParameterInfo>& OutParameterInfo, TArray<FGuid>& OutParameterIds) const
{
	OutParameterInfo.Empty();
}

void UBBMaterialInterfaceStub::GetAllMaterialLayersParameterInfo(TArray<FMaterialParameterInfo>& OutParameterInfo, TArray<FGuid>& OutParameterIds) const
{
	OutParameterInfo.Empty();
}

void UBBMaterialInterfaceStub::GetAllStaticSwitchParameterInfo(TArray<FMaterialParameterInfo>& OutParameterInfo, TArray<FGuid>& OutParameterIds) const
{
	OutParameterInfo.Empty();
}

void UBBMaterialInterfaceStub::GetAllStaticComponentMaskParameterInfo(TArray<FMaterialParameterInfo>& OutParameterInfo, TArray<FGuid>& OutParameterIds) const
{
	OutParameterInfo.Empty();
}

bool UBBMaterialInterfaceStub::IterateDependentFunctions(TFunctionRef<bool(UMaterialFunctionInterface*)> Predicate) const
{
	return false;
}

void UBBMaterialInterfaceStub::GetDependentFunctions(TArray<class UMaterialFunctionInterface*>& DependentFunctions) const
{
	DependentFunctions.Empty();
}

bool UBBMaterialInterfaceStub::GetScalarParameterDefaultValue(const FHashedMaterialParameterInfo & ParameterInfo, float & OutValue, bool bOveriddenOnly, bool bCheckOwnedGlobalOverrides) const
{
	OutValue = 0.0f;

	return false;
}

bool UBBMaterialInterfaceStub::GetVectorParameterDefaultValue(const FHashedMaterialParameterInfo & ParameterInfo, FLinearColor & OutValue, bool bOveriddenOnly, bool bCheckOwnedGlobalOverrides) const
{
	OutValue = FLinearColor();

	return false;
}

bool UBBMaterialInterfaceStub::GetTextureParameterDefaultValue(const FHashedMaterialParameterInfo & ParameterInfo, UTexture *& OutValue, bool bCheckOwnedGlobalOverrides) const
{
	OutValue = nullptr;

	return false;
}

bool UBBMaterialInterfaceStub::GetRuntimeVirtualTextureParameterDefaultValue(const FHashedMaterialParameterInfo & ParameterInfo, URuntimeVirtualTexture *& OutValue, bool bCheckOwnedGlobalOverrides) const
{
	OutValue = nullptr;

	return false;
}

bool UBBMaterialInterfaceStub::GetFontParameterDefaultValue(const FHashedMaterialParameterInfo & ParameterInfo, UFont *& OutFontValue, int32 & OutFontPage, bool bCheckOwnedGlobalOverrides) const
{
	OutFontValue = nullptr;

	return false;
}

bool UBBMaterialInterfaceStub::GetStaticSwitchParameterDefaultValue(const FHashedMaterialParameterInfo & ParameterInfo, bool & OutValue, FGuid & OutExpressionGuid, bool bCheckOwnedGlobalOverrides) const
{
	OutValue = false;

	return false;
}

bool UBBMaterialInterfaceStub::GetStaticComponentMaskParameterDefaultValue(const FHashedMaterialParameterInfo & ParameterInfo, bool & OutR, bool & OutG, bool & OutB, bool & OutA, FGuid & OutExpressionGuid, bool bCheckOwnedGlobalOverrides) const
{
	OutR = 0.0f;
	OutG = 0.0f;
	OutB = 0.0f;
	OutA = 0.0f;

	return false;
}

void UBBMaterialInterfaceStub::GetReferencedTexturesAndOverrides(TSet<const UTexture*>& InOutTextures) const
{
	InOutTextures.Empty();
}

int32 UBBMaterialInterfaceStub::GetLayerParameterIndex(EMaterialParameterAssociation Association, UMaterialFunctionInterface * LayerFunction) const
{
	return -1;
}

TArrayView<UObject*const> UBBMaterialInterfaceStub::GetReferencedTextures() const
{
	return TArrayView<UObject*const>();
}

void UBBMaterialInterfaceStub::SaveShaderStableKeysInner(const ITargetPlatform * TP, const FStableShaderKeyAndValue & SaveKeyVal)
{
}

bool UBBMaterialInterfaceStub::GetTexturesInPropertyChain(EMaterialProperty InProperty, TArray<UTexture*>& OutTextures, TArray<FName>* OutTextureParamNames, FStaticParameterSet * InStaticParameterSet, ERHIFeatureLevel::Type InFeatureLevel, EMaterialQualityLevel::Type InQuality)
{
	OutTextures.Empty();

	return false;
}
