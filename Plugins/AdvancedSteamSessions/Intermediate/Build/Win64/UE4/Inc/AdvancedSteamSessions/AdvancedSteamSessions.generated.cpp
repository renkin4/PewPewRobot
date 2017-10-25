// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "AdvancedSteamSessions.generated.dep.h"
PRAGMA_DISABLE_OPTIMIZATION
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCode1AdvancedSteamSessions() {}
#if USE_COMPILED_IN_NATIVES
// Cross Module References
	ADVANCEDSESSIONS_API class UScriptStruct* Z_Construct_UScriptStruct_FBPUniqueNetId();
	ENGINE_API class UClass* Z_Construct_UClass_UTexture2D_NoRegister();
	ADVANCEDSESSIONS_API class UEnum* Z_Construct_UEnum_AdvancedSessions_EBlueprintAsyncResultSwitch();
	ENGINE_API class UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	COREUOBJECT_API class UClass* Z_Construct_UClass_UObject_NoRegister();
	ENGINE_API class UClass* Z_Construct_UClass_UOnlineBlueprintCallProxyBase();

	ADVANCEDSTEAMSESSIONS_API class UEnum* Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize();
	ADVANCEDSTEAMSESSIONS_API class UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString();
	ADVANCEDSTEAMSESSIONS_API class UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel();
	ADVANCEDSTEAMSESSIONS_API class UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar();
	ADVANCEDSTEAMSESSIONS_API class UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName();
	ADVANCEDSTEAMSESSIONS_API class UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo();
	ADVANCEDSTEAMSESSIONS_API class UClass* Z_Construct_UClass_UAdvancedSteamFriendsLibrary_NoRegister();
	ADVANCEDSTEAMSESSIONS_API class UClass* Z_Construct_UClass_UAdvancedSteamFriendsLibrary();
	ADVANCEDSTEAMSESSIONS_API class UEnum* Z_Construct_UEnum_AdvancedSteamSessions_FBPWorkshopFileType();
	ADVANCEDSTEAMSESSIONS_API class UEnum* Z_Construct_UEnum_AdvancedSteamSessions_FBPSteamResult();
	ADVANCEDSTEAMSESSIONS_API class UScriptStruct* Z_Construct_UScriptStruct_FBPSteamWorkshopItemDetails();
	ADVANCEDSTEAMSESSIONS_API class UScriptStruct* Z_Construct_UScriptStruct_FBPSteamWorkshopID();
	ADVANCEDSTEAMSESSIONS_API class UFunction* Z_Construct_UFunction_UAdvancedSteamWorkshopLibrary_GetNumSubscribedWorkshopItems();
	ADVANCEDSTEAMSESSIONS_API class UFunction* Z_Construct_UFunction_UAdvancedSteamWorkshopLibrary_GetSubscribedWorkshopItems();
	ADVANCEDSTEAMSESSIONS_API class UClass* Z_Construct_UClass_UAdvancedSteamWorkshopLibrary_NoRegister();
	ADVANCEDSTEAMSESSIONS_API class UClass* Z_Construct_UClass_UAdvancedSteamWorkshopLibrary();
	ADVANCEDSTEAMSESSIONS_API class UFunction* Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature();
	ADVANCEDSTEAMSESSIONS_API class UFunction* Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails();
	ADVANCEDSTEAMSESSIONS_API class UClass* Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_NoRegister();
	ADVANCEDSTEAMSESSIONS_API class UClass* Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy();
	ADVANCEDSTEAMSESSIONS_API class UPackage* Z_Construct_UPackage__Script_AdvancedSteamSessions();
static UEnum* SteamAvatarSize_StaticEnum()
{
	extern ADVANCEDSTEAMSESSIONS_API class UPackage* Z_Construct_UPackage__Script_AdvancedSteamSessions();
	static UEnum* Singleton = nullptr;
	if (!Singleton)
	{
		extern ADVANCEDSTEAMSESSIONS_API class UEnum* Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize();
		Singleton = GetStaticEnum(Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize, Z_Construct_UPackage__Script_AdvancedSteamSessions(), TEXT("SteamAvatarSize"));
	}
	return Singleton;
}
static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_SteamAvatarSize(SteamAvatarSize_StaticEnum, TEXT("/Script/AdvancedSteamSessions"), TEXT("SteamAvatarSize"), false, nullptr, nullptr);
	UEnum* Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize()
	{
		UPackage* Outer=Z_Construct_UPackage__Script_AdvancedSteamSessions();
		extern uint32 Get_Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize_CRC();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("SteamAvatarSize"), 0, Get_Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize_CRC(), false);
		if (!ReturnEnum)
		{
			ReturnEnum = new(EC_InternalUseOnlyConstructor, Outer, TEXT("SteamAvatarSize"), RF_Public|RF_Transient|RF_MarkAsNative) UEnum(FObjectInitializer());
			TArray<TPair<FName, int64>> EnumNames;
			EnumNames.Emplace(TEXT("SteamAvatarSize::SteamAvatar_Small"), 1);
			EnumNames.Emplace(TEXT("SteamAvatarSize::SteamAvatar_Medium"), 2);
			EnumNames.Emplace(TEXT("SteamAvatarSize::SteamAvatar_Large"), 3);
			EnumNames.Emplace(TEXT("SteamAvatarSize::SteamAvatar_MAX"), 4);
			ReturnEnum->SetEnums(EnumNames, UEnum::ECppForm::EnumClass);
			ReturnEnum->CppType = TEXT("SteamAvatarSize");
#if WITH_METADATA
			UMetaData* MetaData = ReturnEnum->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnEnum, TEXT("BlueprintType"), TEXT("true"));
			MetaData->SetValue(ReturnEnum, TEXT("IsBlueprintBase"), TEXT("true"));
			MetaData->SetValue(ReturnEnum, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamFriendsLibrary.h"));
#endif
		}
		return ReturnEnum;
	}
	uint32 Get_Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize_CRC() { return 2535999010U; }
	void UAdvancedSteamFriendsLibrary::StaticRegisterNativesUAdvancedSteamFriendsLibrary()
	{
		UClass* Class = UAdvancedSteamFriendsLibrary::StaticClass();
		static const TNameNativePtrPair<ANSICHAR> AnsiFuncs[] = {
			{ "CreateSteamIDFromString", (Native)&UAdvancedSteamFriendsLibrary::execCreateSteamIDFromString },
			{ "GetFriendSteamLevel", (Native)&UAdvancedSteamFriendsLibrary::execGetFriendSteamLevel },
			{ "GetSteamFriendAvatar", (Native)&UAdvancedSteamFriendsLibrary::execGetSteamFriendAvatar },
			{ "GetSteamPersonaName", (Native)&UAdvancedSteamFriendsLibrary::execGetSteamPersonaName },
			{ "RequestSteamFriendInfo", (Native)&UAdvancedSteamFriendsLibrary::execRequestSteamFriendInfo },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, AnsiFuncs, 5);
	}
	UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString()
	{
		struct AdvancedSteamFriendsLibrary_eventCreateSteamIDFromString_Parms
		{
			FString SteamID64;
			FBPUniqueNetId ReturnValue;
		};
		UObject* Outer=Z_Construct_UClass_UAdvancedSteamFriendsLibrary();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("CreateSteamIDFromString"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x14022401, 65535, sizeof(AdvancedSteamFriendsLibrary_eventCreateSteamIDFromString_Parms));
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(ReturnValue, AdvancedSteamFriendsLibrary_eventCreateSteamIDFromString_Parms), 0x0010000000000580, Z_Construct_UScriptStruct_FBPUniqueNetId());
			UProperty* NewProp_SteamID64 = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("SteamID64"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(SteamID64, AdvancedSteamFriendsLibrary_eventCreateSteamIDFromString_Parms), 0x0010000000000082);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Online|AdvancedFriends|SteamAPI"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamFriendsLibrary.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("Creates a unique steam id directly from a string holding a uint64 value, useful for testing"));
			MetaData->SetValue(NewProp_SteamID64, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel()
	{
		struct AdvancedSteamFriendsLibrary_eventGetFriendSteamLevel_Parms
		{
			FBPUniqueNetId UniqueNetId;
			int32 ReturnValue;
		};
		UObject* Outer=Z_Construct_UClass_UAdvancedSteamFriendsLibrary();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("GetFriendSteamLevel"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04022401, 65535, sizeof(AdvancedSteamFriendsLibrary_eventGetFriendSteamLevel_Parms));
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(CPP_PROPERTY_BASE(ReturnValue, AdvancedSteamFriendsLibrary_eventGetFriendSteamLevel_Parms), 0x0010000000000580);
			UProperty* NewProp_UniqueNetId = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("UniqueNetId"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(UniqueNetId, AdvancedSteamFriendsLibrary_eventGetFriendSteamLevel_Parms), 0x0010000000000082, Z_Construct_UScriptStruct_FBPUniqueNetId());
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Online|AdvancedFriends|SteamAPI"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamFriendsLibrary.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("Gets the level of a friends steam account, STEAM ONLY, Returns -1 if the steam level is not known, might need RequestSteamFriendInfo called first."));
			MetaData->SetValue(NewProp_UniqueNetId, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar()
	{
		struct AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms
		{
			FBPUniqueNetId UniqueNetId;
			EBlueprintAsyncResultSwitch Result;
			SteamAvatarSize AvatarSize;
			UTexture2D* ReturnValue;
		};
		UObject* Outer=Z_Construct_UClass_UAdvancedSteamFriendsLibrary();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("GetSteamFriendAvatar"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04422401, 65535, sizeof(AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms));
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(ReturnValue, AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms), 0x0010000000000580, Z_Construct_UClass_UTexture2D_NoRegister());
			UProperty* NewProp_AvatarSize = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("AvatarSize"), RF_Public|RF_Transient|RF_MarkAsNative) UEnumProperty(CPP_PROPERTY_BASE(AvatarSize, AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms), 0x0010000000000080, Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize());
			UProperty* NewProp_AvatarSize_Underlying = new(EC_InternalUseOnlyConstructor, NewProp_AvatarSize, TEXT("UnderlyingType"), RF_Public|RF_Transient|RF_MarkAsNative) UByteProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000);
			UProperty* NewProp_Result = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("Result"), RF_Public|RF_Transient|RF_MarkAsNative) UEnumProperty(CPP_PROPERTY_BASE(Result, AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms), 0x0010000000000180, Z_Construct_UEnum_AdvancedSessions_EBlueprintAsyncResultSwitch());
			UProperty* NewProp_Result_Underlying = new(EC_InternalUseOnlyConstructor, NewProp_Result, TEXT("UnderlyingType"), RF_Public|RF_Transient|RF_MarkAsNative) UByteProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000);
			UProperty* NewProp_UniqueNetId = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("UniqueNetId"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(UniqueNetId, AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms), 0x0010000000000082, Z_Construct_UScriptStruct_FBPUniqueNetId());
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Online|AdvancedFriends|SteamAPI"));
			MetaData->SetValue(ReturnFunction, TEXT("CPP_Default_AvatarSize"), TEXT("SteamAvatar_Medium"));
			MetaData->SetValue(ReturnFunction, TEXT("ExpandEnumAsExecs"), TEXT("Result"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamFriendsLibrary.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("Get a texture of a valid friends avatar, STEAM ONLY, Returns invalid texture if the subsystem hasn't loaded that size of avatar yet"));
			MetaData->SetValue(NewProp_UniqueNetId, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName()
	{
		struct AdvancedSteamFriendsLibrary_eventGetSteamPersonaName_Parms
		{
			FBPUniqueNetId UniqueNetId;
			FString ReturnValue;
		};
		UObject* Outer=Z_Construct_UClass_UAdvancedSteamFriendsLibrary();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("GetSteamPersonaName"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04022401, 65535, sizeof(AdvancedSteamFriendsLibrary_eventGetSteamPersonaName_Parms));
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(ReturnValue, AdvancedSteamFriendsLibrary_eventGetSteamPersonaName_Parms), 0x0010000000000580);
			UProperty* NewProp_UniqueNetId = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("UniqueNetId"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(UniqueNetId, AdvancedSteamFriendsLibrary_eventGetSteamPersonaName_Parms), 0x0010000000000082, Z_Construct_UScriptStruct_FBPUniqueNetId());
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Online|AdvancedFriends|SteamAPI"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamFriendsLibrary.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("Gets the persona name of a steam ID, STEAM ONLY, Returns empty if no result, might need RequestSteamFriendInfo called first."));
			MetaData->SetValue(NewProp_UniqueNetId, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo()
	{
		struct AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms
		{
			FBPUniqueNetId UniqueNetId;
			bool bRequireNameOnly;
			bool ReturnValue;
		};
		UObject* Outer=Z_Construct_UClass_UAdvancedSteamFriendsLibrary();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("RequestSteamFriendInfo"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04022401, 65535, sizeof(AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms));
			CPP_BOOL_PROPERTY_BITMASK_STRUCT(ReturnValue, AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms, bool);
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(ReturnValue, AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms), 0x0010000000000580, CPP_BOOL_PROPERTY_BITMASK(ReturnValue, AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms), sizeof(bool), true);
			CPP_BOOL_PROPERTY_BITMASK_STRUCT(bRequireNameOnly, AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms, bool);
			UProperty* NewProp_bRequireNameOnly = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("bRequireNameOnly"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(bRequireNameOnly, AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms), 0x0010000000000080, CPP_BOOL_PROPERTY_BITMASK(bRequireNameOnly, AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms), sizeof(bool), true);
			UProperty* NewProp_UniqueNetId = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("UniqueNetId"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(UniqueNetId, AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms), 0x0010000000000082, Z_Construct_UScriptStruct_FBPUniqueNetId());
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Online|AdvancedFriends|SteamAPI"));
			MetaData->SetValue(ReturnFunction, TEXT("CPP_Default_bRequireNameOnly"), TEXT("false"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamFriendsLibrary.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("Preloads the avatar and name of a steam friend, return whether it is already available or not, STEAM ONLY, Takes time to actually load everything after this is called."));
			MetaData->SetValue(NewProp_UniqueNetId, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UAdvancedSteamFriendsLibrary_NoRegister()
	{
		return UAdvancedSteamFriendsLibrary::StaticClass();
	}
	UClass* Z_Construct_UClass_UAdvancedSteamFriendsLibrary()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UBlueprintFunctionLibrary();
			Z_Construct_UPackage__Script_AdvancedSteamSessions();
			OuterClass = UAdvancedSteamFriendsLibrary::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20000080;

				OuterClass->LinkChild(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString());
				OuterClass->LinkChild(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel());
				OuterClass->LinkChild(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar());
				OuterClass->LinkChild(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName());
				OuterClass->LinkChild(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo());

				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString(), "CreateSteamIDFromString"); // 3274121421
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel(), "GetFriendSteamLevel"); // 2369316772
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar(), "GetSteamFriendAvatar"); // 2356272692
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName(), "GetSteamPersonaName"); // 722806983
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo(), "RequestSteamFriendInfo"); // 3711958295
				static TCppClassTypeInfo<TCppClassTypeTraits<UAdvancedSteamFriendsLibrary> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("AdvancedSteamFriendsLibrary.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamFriendsLibrary.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAdvancedSteamFriendsLibrary, 3824844171);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAdvancedSteamFriendsLibrary(Z_Construct_UClass_UAdvancedSteamFriendsLibrary, &UAdvancedSteamFriendsLibrary::StaticClass, TEXT("/Script/AdvancedSteamSessions"), TEXT("UAdvancedSteamFriendsLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAdvancedSteamFriendsLibrary);
static UEnum* FBPWorkshopFileType_StaticEnum()
{
	extern ADVANCEDSTEAMSESSIONS_API class UPackage* Z_Construct_UPackage__Script_AdvancedSteamSessions();
	static UEnum* Singleton = nullptr;
	if (!Singleton)
	{
		extern ADVANCEDSTEAMSESSIONS_API class UEnum* Z_Construct_UEnum_AdvancedSteamSessions_FBPWorkshopFileType();
		Singleton = GetStaticEnum(Z_Construct_UEnum_AdvancedSteamSessions_FBPWorkshopFileType, Z_Construct_UPackage__Script_AdvancedSteamSessions(), TEXT("FBPWorkshopFileType"));
	}
	return Singleton;
}
static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_FBPWorkshopFileType(FBPWorkshopFileType_StaticEnum, TEXT("/Script/AdvancedSteamSessions"), TEXT("FBPWorkshopFileType"), false, nullptr, nullptr);
	UEnum* Z_Construct_UEnum_AdvancedSteamSessions_FBPWorkshopFileType()
	{
		UPackage* Outer=Z_Construct_UPackage__Script_AdvancedSteamSessions();
		extern uint32 Get_Z_Construct_UEnum_AdvancedSteamSessions_FBPWorkshopFileType_CRC();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("FBPWorkshopFileType"), 0, Get_Z_Construct_UEnum_AdvancedSteamSessions_FBPWorkshopFileType_CRC(), false);
		if (!ReturnEnum)
		{
			ReturnEnum = new(EC_InternalUseOnlyConstructor, Outer, TEXT("FBPWorkshopFileType"), RF_Public|RF_Transient|RF_MarkAsNative) UEnum(FObjectInitializer());
			TArray<TPair<FName, int64>> EnumNames;
			EnumNames.Emplace(TEXT("FBPWorkshopFileType::k_EWorkshopFileTypeCommunity"), 0);
			EnumNames.Emplace(TEXT("FBPWorkshopFileType::k_EWorkshopFileTypeMicrotransaction"), 1);
			EnumNames.Emplace(TEXT("FBPWorkshopFileType::k_EWorkshopFileTypeCollection"), 2);
			EnumNames.Emplace(TEXT("FBPWorkshopFileType::k_EWorkshopFileTypeArt"), 3);
			EnumNames.Emplace(TEXT("FBPWorkshopFileType::k_EWorkshopFileTypeVideo"), 4);
			EnumNames.Emplace(TEXT("FBPWorkshopFileType::k_EWorkshopFileTypeScreenshot"), 5);
			EnumNames.Emplace(TEXT("FBPWorkshopFileType::k_EWorkshopFileTypeGame"), 6);
			EnumNames.Emplace(TEXT("FBPWorkshopFileType::k_EWorkshopFileTypeSoftware"), 7);
			EnumNames.Emplace(TEXT("FBPWorkshopFileType::k_EWorkshopFileTypeConcept"), 8);
			EnumNames.Emplace(TEXT("FBPWorkshopFileType::k_EWorkshopFileTypeWebGuide"), 9);
			EnumNames.Emplace(TEXT("FBPWorkshopFileType::k_EWorkshopFileTypeIntegratedGuide"), 10);
			EnumNames.Emplace(TEXT("FBPWorkshopFileType::k_EWorkshopFileTypeMerch"), 11);
			EnumNames.Emplace(TEXT("FBPWorkshopFileType::k_EWorkshopFileTypeControllerBinding"), 12);
			EnumNames.Emplace(TEXT("FBPWorkshopFileType::k_EWorkshopFileTypeSteamworksAccessInvite"), 13);
			EnumNames.Emplace(TEXT("FBPWorkshopFileType::k_EWorkshopFileTypeSteamVideo"), 14);
			EnumNames.Emplace(TEXT("FBPWorkshopFileType::k_EWorkshopFileTypeMax"), 15);
			EnumNames.Emplace(TEXT("FBPWorkshopFileType::k_MAX"), 16);
			ReturnEnum->SetEnums(EnumNames, UEnum::ECppForm::EnumClass);
			ReturnEnum->CppType = TEXT("FBPWorkshopFileType");
#if WITH_METADATA
			UMetaData* MetaData = ReturnEnum->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnEnum, TEXT("BlueprintType"), TEXT("true"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EWorkshopFileTypeMax.ToolTip"), TEXT("Update k_EWorkshopFileTypeMax if you add values."));
			MetaData->SetValue(ReturnEnum, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(ReturnEnum, TEXT("ToolTip"), TEXT("Check these to future proof"));
#endif
		}
		return ReturnEnum;
	}
	uint32 Get_Z_Construct_UEnum_AdvancedSteamSessions_FBPWorkshopFileType_CRC() { return 188216730U; }
static UEnum* FBPSteamResult_StaticEnum()
{
	extern ADVANCEDSTEAMSESSIONS_API class UPackage* Z_Construct_UPackage__Script_AdvancedSteamSessions();
	static UEnum* Singleton = nullptr;
	if (!Singleton)
	{
		extern ADVANCEDSTEAMSESSIONS_API class UEnum* Z_Construct_UEnum_AdvancedSteamSessions_FBPSteamResult();
		Singleton = GetStaticEnum(Z_Construct_UEnum_AdvancedSteamSessions_FBPSteamResult, Z_Construct_UPackage__Script_AdvancedSteamSessions(), TEXT("FBPSteamResult"));
	}
	return Singleton;
}
static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_FBPSteamResult(FBPSteamResult_StaticEnum, TEXT("/Script/AdvancedSteamSessions"), TEXT("FBPSteamResult"), false, nullptr, nullptr);
	UEnum* Z_Construct_UEnum_AdvancedSteamSessions_FBPSteamResult()
	{
		UPackage* Outer=Z_Construct_UPackage__Script_AdvancedSteamSessions();
		extern uint32 Get_Z_Construct_UEnum_AdvancedSteamSessions_FBPSteamResult_CRC();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("FBPSteamResult"), 0, Get_Z_Construct_UEnum_AdvancedSteamSessions_FBPSteamResult_CRC(), false);
		if (!ReturnEnum)
		{
			ReturnEnum = new(EC_InternalUseOnlyConstructor, Outer, TEXT("FBPSteamResult"), RF_Public|RF_Transient|RF_MarkAsNative) UEnum(FObjectInitializer());
			TArray<TPair<FName, int64>> EnumNames;
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultOK"), 1);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultFail"), 2);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultNoConnection"), 3);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultInvalidPassword"), 5);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultLoggedInElsewhere"), 6);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultInvalidProtocolVer"), 7);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultInvalidParam"), 8);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultFileNotFound"), 9);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultBusy"), 10);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultInvalidState"), 11);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultInvalidName"), 12);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultInvalidEmail"), 13);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultDuplicateName"), 14);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultAccessDenied"), 15);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultTimeout"), 16);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultBanned"), 17);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultAccountNotFound"), 18);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultInvalidSteamID"), 19);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultServiceUnavailable"), 20);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultNotLoggedOn"), 21);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultPending"), 22);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultEncryptionFailure"), 23);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultInsufficientPrivilege"), 24);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultLimitExceeded"), 25);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultRevoked"), 26);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultExpired"), 27);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultAlreadyRedeemed"), 28);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultDuplicateRequest"), 29);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultAlreadyOwned"), 30);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultIPNotFound"), 31);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultPersistFailed"), 32);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultLockingFailed"), 33);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultLogonSessionReplaced"), 34);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultConnectFailed"), 35);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultHandshakeFailed"), 36);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultIOFailure"), 37);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultRemoteDisconnect"), 38);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultShoppingCartNotFound"), 39);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultBlocked"), 40);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultIgnored"), 41);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultNoMatch"), 42);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultAccountDisabled"), 43);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultServiceReadOnly"), 44);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultAccountNotFeatured"), 45);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultAdministratorOK"), 46);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultContentVersion"), 47);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultTryAnotherCM"), 48);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultPasswordRequiredToKickSession"), 49);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultAlreadyLoggedInElsewhere"), 50);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultSuspended"), 51);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultCancelled"), 52);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultDataCorruption"), 53);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultDiskFull"), 54);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultRemoteCallFailed"), 55);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultPasswordUnset"), 56);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultExternalAccountUnlinked"), 57);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultPSNTicketInvalid"), 58);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultExternalAccountAlreadyLinked"), 59);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultRemoteFileConflict"), 60);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultIllegalPassword"), 61);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultSameAsPreviousValue"), 62);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultAccountLogonDenied"), 63);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultCannotUseOldPassword"), 64);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultInvalidLoginAuthCode"), 65);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultAccountLogonDeniedNoMail"), 66);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultHardwareNotCapableOfIPT"), 67);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultIPTInitError"), 68);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultParentalControlRestricted"), 69);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultFacebookQueryError"), 70);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultExpiredLoginAuthCode"), 71);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultIPLoginRestrictionFailed"), 72);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultAccountLockedDown"), 73);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultAccountLogonDeniedVerifiedEmailRequired"), 74);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultNoMatchingURL"), 75);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultBadResponse"), 76);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultRequirePasswordReEntry"), 77);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultValueOutOfRange"), 78);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultUnexpectedError"), 79);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultDisabled"), 80);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultInvalidCEGSubmission"), 81);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultRestrictedDevice"), 82);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultRegionLocked"), 83);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultRateLimitExceeded"), 84);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultAccountLoginDeniedNeedTwoFactor"), 85);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultItemDeleted"), 86);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultAccountLoginDeniedThrottle"), 87);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultTwoFactorCodeMismatch"), 88);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultTwoFactorActivationCodeMismatch"), 89);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultAccountAssociatedToMultiplePartners"), 90);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_EResultNotModified"), 91);
			EnumNames.Emplace(TEXT("FBPSteamResult::k_MAX"), 92);
			ReturnEnum->SetEnums(EnumNames, UEnum::ECppForm::EnumClass);
			ReturnEnum->CppType = TEXT("FBPSteamResult");
#if WITH_METADATA
			UMetaData* MetaData = ReturnEnum->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnEnum, TEXT("BlueprintType"), TEXT("true"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultAccessDenied.ToolTip"), TEXT("name is not unique"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultAccountAssociatedToMultiplePartners.ToolTip"), TEXT("activation code for two-factor didn't match"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultAccountDisabled.ToolTip"), TEXT("nothing matching the request found"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultAccountLoginDeniedNeedTwoFactor.ToolTip"), TEXT("Temporary rate limit exceeded, try again later, different from k_EResultLimitExceeded which may be permanent"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultAccountLoginDeniedThrottle.ToolTip"), TEXT("The thing we're trying to access has been deleted"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultAccountLogonDenied.ToolTip"), TEXT("new value is the same as the old one ( secret question and answer )"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultAccountLogonDeniedNoMail.ToolTip"), TEXT("account login denied due to auth code invalid"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultAccountNotFeatured.ToolTip"), TEXT("this service is not accepting content changes right now"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultAccountNotFound.ToolTip"), TEXT("VAC2 banned"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultAdministratorOK.ToolTip"), TEXT("account doesn't have value, so this feature isn't available"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultAlreadyLoggedInElsewhere.ToolTip"), TEXT("You are already logged in elsewhere, this cached credential login has failed."));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultAlreadyOwned.ToolTip"), TEXT("The request is a duplicate and the action has already occurred in the past, ignored this time"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultAlreadyRedeemed.ToolTip"), TEXT("License/Guest pass the user is trying to access is expired"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultBanned.ToolTip"), TEXT("operation timed out"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultBlocked.ToolTip"), TEXT("failed to find the shopping cart requested"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultBusy.ToolTip"), TEXT("file was not found"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultCancelled.ToolTip"), TEXT("Long running operation (content download) suspended/paused"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultCannotUseOldPassword.ToolTip"), TEXT("account login denied due to 2nd factor authentication failure"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultContentVersion.ToolTip"), TEXT("allowed to take this action, but only because requester is admin"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultDataCorruption.ToolTip"), TEXT("Operation canceled (typically by user: content download)"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultDisabled.ToolTip"), TEXT("something happened that we didn't expect to ever happen"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultDiskFull.ToolTip"), TEXT("Operation canceled because data is ill formed or unrecoverable"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultDuplicateName.ToolTip"), TEXT("email is invalid"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultDuplicateRequest.ToolTip"), TEXT("Guest pass has already been redeemed by account, cannot be acked again"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultEncryptionFailure.ToolTip"), TEXT("Request is pending (may be in process, or waiting on third party)"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultExpired.ToolTip"), TEXT("Access has been revoked (used for revoked guest passes)"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultExpiredLoginAuthCode.ToolTip"), TEXT("Facebook query returned an error"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultExternalAccountAlreadyLinked.ToolTip"), TEXT("PSN ticket was invalid"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultExternalAccountUnlinked.ToolTip"), TEXT("Password could not be verified as it's unset server side"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultFacebookQueryError.ToolTip"), TEXT("operation failed due to parental control restrictions for current user"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultFail.ToolTip"), TEXT("success"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultFileNotFound.ToolTip"), TEXT("a parameter is incorrect"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultHardwareNotCapableOfIPT.ToolTip"), TEXT("account login denied due to 2nd factor auth failure - and no mail has been sent"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultIgnored.ToolTip"), TEXT("a user didn't allow it"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultIllegalPassword.ToolTip"), TEXT("The sync cannot resume due to a conflict between the local and remote files"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultInsufficientPrivilege.ToolTip"), TEXT("Encryption or Decryption failed"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultInvalidCEGSubmission.ToolTip"), TEXT("The requested service has been configured to be unavailable"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultInvalidEmail.ToolTip"), TEXT("name is invalid"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultInvalidLoginAuthCode.ToolTip"), TEXT("The requested new password is not legal"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultInvalidName.ToolTip"), TEXT("called object was in an invalid state"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultInvalidParam.ToolTip"), TEXT("protocol version is incorrect"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultInvalidPassword.ToolTip"), TEXT("no/failed network connection\n      k_EResultNoConnectionRetry = 4,                          OBSOLETE - removed"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultInvalidProtocolVer.ToolTip"), TEXT("same user logged in elsewhere"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultInvalidState.ToolTip"), TEXT("called method busy - action not taken"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultInvalidSteamID.ToolTip"), TEXT("account not found"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultIPLoginRestrictionFailed.ToolTip"), TEXT("account login denied due to auth code expired"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultIPNotFound.ToolTip"), TEXT("All the games in this guest pass redemption request are already owned by the user"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultItemDeleted.ToolTip"), TEXT("Need two-factor code to login"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultLimitExceeded.ToolTip"), TEXT("Insufficient privilege"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultLockingFailed.ToolTip"), TEXT("failed to write change to the data store"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultLoggedInElsewhere.ToolTip"), TEXT("password/ticket is invalid"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultLogonSessionReplaced.ToolTip"), TEXT("failed to acquire access lock for this operation"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultNoConnection.ToolTip"), TEXT("generic failure"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultNoMatch.ToolTip"), TEXT("target is ignoring sender"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultNotLoggedOn.ToolTip"), TEXT("The requested service is currently unavailable"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultNotModified.ToolTip"), TEXT("account has been associated with multiple partners"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultPasswordRequiredToKickSession.ToolTip"), TEXT("The current CM can't service the user making a request, user should try another."));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultPasswordUnset.ToolTip"), TEXT("an remote call or IPC call failed"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultPending.ToolTip"), TEXT("The user is not logged on"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultPersistFailed.ToolTip"), TEXT("IP address not found"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultPSNTicketInvalid.ToolTip"), TEXT("External account (PSN, Facebook...) is not linked to a Steam account"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultRateLimitExceeded.ToolTip"), TEXT("The action could not be complete because it is region restricted"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultRegionLocked.ToolTip"), TEXT("The device being used is not allowed to perform this action"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultRemoteCallFailed.ToolTip"), TEXT("Operation canceled - not enough disk space."));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultRemoteFileConflict.ToolTip"), TEXT("External account (PSN, Facebook...) is already linked to some other account, must explicitly request to replace/delete the link first"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultRequirePasswordReEntry.ToolTip"), TEXT("parse failure, missing field, etc."));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultRestrictedDevice.ToolTip"), TEXT("The set of files submitted to the CEG server are not valid !"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultRevoked.ToolTip"), TEXT("Too much of a good thing"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultSameAsPreviousValue.ToolTip"), TEXT("The requested new password is not legal"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultServiceUnavailable.ToolTip"), TEXT("steamID is invalid"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultSuspended.ToolTip"), TEXT("You are already logged in elsewhere, you must wait"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultTimeout.ToolTip"), TEXT("access is denied"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultTryAnotherCM.ToolTip"), TEXT("A Version mismatch in content transmitted within the Steam protocol."));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultTwoFactorActivationCodeMismatch.ToolTip"), TEXT("two factor code mismatch"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultTwoFactorCodeMismatch.ToolTip"), TEXT("login attempt failed, try to throttle response to possible attacker"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultUnexpectedError.ToolTip"), TEXT("the value entered is outside the acceptable range"));
			MetaData->SetValue(ReturnEnum, TEXT("k_EResultValueOutOfRange.ToolTip"), TEXT("The user cannot complete the action until they re-enter their password"));
			MetaData->SetValue(ReturnEnum, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(ReturnEnum, TEXT("ToolTip"), TEXT("General result codes - Copying steams version over\nCheck these to future proof"));
#endif
		}
		return ReturnEnum;
	}
	uint32 Get_Z_Construct_UEnum_AdvancedSteamSessions_FBPSteamResult_CRC() { return 1386788399U; }
class UScriptStruct* FBPSteamWorkshopItemDetails::StaticStruct()
{
	extern ADVANCEDSTEAMSESSIONS_API class UPackage* Z_Construct_UPackage__Script_AdvancedSteamSessions();
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ADVANCEDSTEAMSESSIONS_API class UScriptStruct* Z_Construct_UScriptStruct_FBPSteamWorkshopItemDetails();
		extern ADVANCEDSTEAMSESSIONS_API uint32 Get_Z_Construct_UScriptStruct_FBPSteamWorkshopItemDetails_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FBPSteamWorkshopItemDetails, Z_Construct_UPackage__Script_AdvancedSteamSessions(), TEXT("BPSteamWorkshopItemDetails"), sizeof(FBPSteamWorkshopItemDetails), Get_Z_Construct_UScriptStruct_FBPSteamWorkshopItemDetails_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FBPSteamWorkshopItemDetails(FBPSteamWorkshopItemDetails::StaticStruct, TEXT("/Script/AdvancedSteamSessions"), TEXT("BPSteamWorkshopItemDetails"), false, nullptr, nullptr);
static struct FScriptStruct_AdvancedSteamSessions_StaticRegisterNativesFBPSteamWorkshopItemDetails
{
	FScriptStruct_AdvancedSteamSessions_StaticRegisterNativesFBPSteamWorkshopItemDetails()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("BPSteamWorkshopItemDetails")),new UScriptStruct::TCppStructOps<FBPSteamWorkshopItemDetails>);
	}
} ScriptStruct_AdvancedSteamSessions_StaticRegisterNativesFBPSteamWorkshopItemDetails;
	UScriptStruct* Z_Construct_UScriptStruct_FBPSteamWorkshopItemDetails()
	{
		UPackage* Outer = Z_Construct_UPackage__Script_AdvancedSteamSessions();
		extern uint32 Get_Z_Construct_UScriptStruct_FBPSteamWorkshopItemDetails_CRC();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("BPSteamWorkshopItemDetails"), sizeof(FBPSteamWorkshopItemDetails), Get_Z_Construct_UScriptStruct_FBPSteamWorkshopItemDetails_CRC(), false);
		if (!ReturnStruct)
		{
			ReturnStruct = new(EC_InternalUseOnlyConstructor, Outer, TEXT("BPSteamWorkshopItemDetails"), RF_Public|RF_Transient|RF_MarkAsNative) UScriptStruct(FObjectInitializer(), NULL, new UScriptStruct::TCppStructOps<FBPSteamWorkshopItemDetails>, EStructFlags(0x00000001));
			UProperty* NewProp_CreatorSteamID = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("CreatorSteamID"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(CreatorSteamID, FBPSteamWorkshopItemDetails), 0x0010000000000015);
			CPP_BOOL_PROPERTY_BITMASK_STRUCT(bTagsTruncated, FBPSteamWorkshopItemDetails, bool);
			UProperty* NewProp_bTagsTruncated = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("bTagsTruncated"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(bTagsTruncated, FBPSteamWorkshopItemDetails), 0x0010000000000015, CPP_BOOL_PROPERTY_BITMASK(bTagsTruncated, FBPSteamWorkshopItemDetails), sizeof(bool), true);
			CPP_BOOL_PROPERTY_BITMASK_STRUCT(bAcceptedForUse, FBPSteamWorkshopItemDetails, bool);
			UProperty* NewProp_bAcceptedForUse = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("bAcceptedForUse"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(bAcceptedForUse, FBPSteamWorkshopItemDetails), 0x0010000000000015, CPP_BOOL_PROPERTY_BITMASK(bAcceptedForUse, FBPSteamWorkshopItemDetails), sizeof(bool), true);
			CPP_BOOL_PROPERTY_BITMASK_STRUCT(bBanned, FBPSteamWorkshopItemDetails, bool);
			UProperty* NewProp_bBanned = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("bBanned"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(bBanned, FBPSteamWorkshopItemDetails), 0x0010000000000015, CPP_BOOL_PROPERTY_BITMASK(bBanned, FBPSteamWorkshopItemDetails), sizeof(bool), true);
			UProperty* NewProp_CalculatedScore = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("CalculatedScore"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(CalculatedScore, FBPSteamWorkshopItemDetails), 0x0010000000000015);
			UProperty* NewProp_VotesDown = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("VotesDown"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(CPP_PROPERTY_BASE(VotesDown, FBPSteamWorkshopItemDetails), 0x0010000000000015);
			UProperty* NewProp_VotesUp = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("VotesUp"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(CPP_PROPERTY_BASE(VotesUp, FBPSteamWorkshopItemDetails), 0x0010000000000015);
			UProperty* NewProp_ItemUrl = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("ItemUrl"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(ItemUrl, FBPSteamWorkshopItemDetails), 0x0010000000000015);
			UProperty* NewProp_Description = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("Description"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(Description, FBPSteamWorkshopItemDetails), 0x0010000000000015);
			UProperty* NewProp_Title = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("Title"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(Title, FBPSteamWorkshopItemDetails), 0x0010000000000015);
			UProperty* NewProp_ConsumerAppID = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("ConsumerAppID"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(CPP_PROPERTY_BASE(ConsumerAppID, FBPSteamWorkshopItemDetails), 0x0010000000000015);
			UProperty* NewProp_CreatorAppID = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("CreatorAppID"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(CPP_PROPERTY_BASE(CreatorAppID, FBPSteamWorkshopItemDetails), 0x0010000000000015);
			UProperty* NewProp_FileType = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("FileType"), RF_Public|RF_Transient|RF_MarkAsNative) UEnumProperty(CPP_PROPERTY_BASE(FileType, FBPSteamWorkshopItemDetails), 0x0010000000000015, Z_Construct_UEnum_AdvancedSteamSessions_FBPWorkshopFileType());
			UProperty* NewProp_FileType_Underlying = new(EC_InternalUseOnlyConstructor, NewProp_FileType, TEXT("UnderlyingType"), RF_Public|RF_Transient|RF_MarkAsNative) UByteProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000);
			UProperty* NewProp_ResultOfRequest = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("ResultOfRequest"), RF_Public|RF_Transient|RF_MarkAsNative) UEnumProperty(CPP_PROPERTY_BASE(ResultOfRequest, FBPSteamWorkshopItemDetails), 0x0010000000000015, Z_Construct_UEnum_AdvancedSteamSessions_FBPSteamResult());
			UProperty* NewProp_ResultOfRequest_Underlying = new(EC_InternalUseOnlyConstructor, NewProp_ResultOfRequest, TEXT("UnderlyingType"), RF_Public|RF_Transient|RF_MarkAsNative) UByteProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000);
			ReturnStruct->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnStruct->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnStruct, TEXT("BlueprintType"), TEXT("true"));
			MetaData->SetValue(ReturnStruct, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(ReturnStruct, TEXT("ToolTip"), TEXT("WorkshopItemDetails Struct"));
			MetaData->SetValue(NewProp_CreatorSteamID, TEXT("Category"), TEXT("Online|AdvancedSteamWorkshop"));
			MetaData->SetValue(NewProp_CreatorSteamID, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(NewProp_CreatorSteamID, TEXT("ToolTip"), TEXT("Steam ID of the user who created this content."));
			MetaData->SetValue(NewProp_bTagsTruncated, TEXT("Category"), TEXT("Online|AdvancedSteamWorkshop"));
			MetaData->SetValue(NewProp_bTagsTruncated, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(NewProp_bTagsTruncated, TEXT("ToolTip"), TEXT("whether the list of tags was too long to be returned in the provided buffer"));
			MetaData->SetValue(NewProp_bAcceptedForUse, TEXT("Category"), TEXT("Online|AdvancedSteamWorkshop"));
			MetaData->SetValue(NewProp_bAcceptedForUse, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(NewProp_bAcceptedForUse, TEXT("ToolTip"), TEXT("developer has specifically flagged this item as accepted in the Workshop"));
			MetaData->SetValue(NewProp_bBanned, TEXT("Category"), TEXT("Online|AdvancedSteamWorkshop"));
			MetaData->SetValue(NewProp_bBanned, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(NewProp_bBanned, TEXT("ToolTip"), TEXT("whether the file was banned"));
			MetaData->SetValue(NewProp_CalculatedScore, TEXT("Category"), TEXT("Online|AdvancedSteamWorkshop"));
			MetaData->SetValue(NewProp_CalculatedScore, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(NewProp_CalculatedScore, TEXT("ToolTip"), TEXT("Calculated score"));
			MetaData->SetValue(NewProp_VotesDown, TEXT("Category"), TEXT("Online|AdvancedSteamWorkshop"));
			MetaData->SetValue(NewProp_VotesDown, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(NewProp_VotesUp, TEXT("Category"), TEXT("Online|AdvancedSteamWorkshop"));
			MetaData->SetValue(NewProp_VotesUp, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(NewProp_VotesUp, TEXT("ToolTip"), TEXT("Votes will be unlikely to go above signed limited"));
			MetaData->SetValue(NewProp_ItemUrl, TEXT("Category"), TEXT("Online|AdvancedSteamWorkshop"));
			MetaData->SetValue(NewProp_ItemUrl, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(NewProp_ItemUrl, TEXT("ToolTip"), TEXT("Url for a video of website"));
			MetaData->SetValue(NewProp_Description, TEXT("Category"), TEXT("Online|AdvancedSteamWorkshop"));
			MetaData->SetValue(NewProp_Description, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(NewProp_Description, TEXT("ToolTip"), TEXT("Description of item"));
			MetaData->SetValue(NewProp_Title, TEXT("Category"), TEXT("Online|AdvancedSteamWorkshop"));
			MetaData->SetValue(NewProp_Title, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(NewProp_Title, TEXT("ToolTip"), TEXT("Title of item"));
			MetaData->SetValue(NewProp_ConsumerAppID, TEXT("Category"), TEXT("Online|AdvancedSteamWorkshop"));
			MetaData->SetValue(NewProp_ConsumerAppID, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(NewProp_CreatorAppID, TEXT("Category"), TEXT("Online|AdvancedSteamWorkshop"));
			MetaData->SetValue(NewProp_CreatorAppID, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(NewProp_CreatorAppID, TEXT("ToolTip"), TEXT("These two are listed as baked to an int, but is stored as a uint, think its safe to keep int"));
			MetaData->SetValue(NewProp_FileType, TEXT("Category"), TEXT("Online|AdvancedSteamWorkshop"));
			MetaData->SetValue(NewProp_FileType, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(NewProp_FileType, TEXT("ToolTip"), TEXT("Type of file"));
			MetaData->SetValue(NewProp_ResultOfRequest, TEXT("Category"), TEXT("Online|AdvancedSteamWorkshop"));
			MetaData->SetValue(NewProp_ResultOfRequest, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(NewProp_ResultOfRequest, TEXT("ToolTip"), TEXT("Result of obtaining the details"));
#endif
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FBPSteamWorkshopItemDetails_CRC() { return 626386443U; }
class UScriptStruct* FBPSteamWorkshopID::StaticStruct()
{
	extern ADVANCEDSTEAMSESSIONS_API class UPackage* Z_Construct_UPackage__Script_AdvancedSteamSessions();
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ADVANCEDSTEAMSESSIONS_API class UScriptStruct* Z_Construct_UScriptStruct_FBPSteamWorkshopID();
		extern ADVANCEDSTEAMSESSIONS_API uint32 Get_Z_Construct_UScriptStruct_FBPSteamWorkshopID_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FBPSteamWorkshopID, Z_Construct_UPackage__Script_AdvancedSteamSessions(), TEXT("BPSteamWorkshopID"), sizeof(FBPSteamWorkshopID), Get_Z_Construct_UScriptStruct_FBPSteamWorkshopID_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FBPSteamWorkshopID(FBPSteamWorkshopID::StaticStruct, TEXT("/Script/AdvancedSteamSessions"), TEXT("BPSteamWorkshopID"), false, nullptr, nullptr);
static struct FScriptStruct_AdvancedSteamSessions_StaticRegisterNativesFBPSteamWorkshopID
{
	FScriptStruct_AdvancedSteamSessions_StaticRegisterNativesFBPSteamWorkshopID()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("BPSteamWorkshopID")),new UScriptStruct::TCppStructOps<FBPSteamWorkshopID>);
	}
} ScriptStruct_AdvancedSteamSessions_StaticRegisterNativesFBPSteamWorkshopID;
	UScriptStruct* Z_Construct_UScriptStruct_FBPSteamWorkshopID()
	{
		UPackage* Outer = Z_Construct_UPackage__Script_AdvancedSteamSessions();
		extern uint32 Get_Z_Construct_UScriptStruct_FBPSteamWorkshopID_CRC();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("BPSteamWorkshopID"), sizeof(FBPSteamWorkshopID), Get_Z_Construct_UScriptStruct_FBPSteamWorkshopID_CRC(), false);
		if (!ReturnStruct)
		{
			ReturnStruct = new(EC_InternalUseOnlyConstructor, Outer, TEXT("BPSteamWorkshopID"), RF_Public|RF_Transient|RF_MarkAsNative) UScriptStruct(FObjectInitializer(), NULL, new UScriptStruct::TCppStructOps<FBPSteamWorkshopID>, EStructFlags(0x00000001));
			ReturnStruct->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnStruct->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnStruct, TEXT("BlueprintType"), TEXT("true"));
			MetaData->SetValue(ReturnStruct, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(ReturnStruct, TEXT("ToolTip"), TEXT("Using a custom struct because uint32 isn't blueprint supported and I don't want to cast to int32\ndue to the size of the workshop it could end up overflowing?"));
#endif
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FBPSteamWorkshopID_CRC() { return 1091593715U; }
	void UAdvancedSteamWorkshopLibrary::StaticRegisterNativesUAdvancedSteamWorkshopLibrary()
	{
		UClass* Class = UAdvancedSteamWorkshopLibrary::StaticClass();
		static const TNameNativePtrPair<ANSICHAR> AnsiFuncs[] = {
			{ "GetNumSubscribedWorkshopItems", (Native)&UAdvancedSteamWorkshopLibrary::execGetNumSubscribedWorkshopItems },
			{ "GetSubscribedWorkshopItems", (Native)&UAdvancedSteamWorkshopLibrary::execGetSubscribedWorkshopItems },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, AnsiFuncs, 2);
	}
	UFunction* Z_Construct_UFunction_UAdvancedSteamWorkshopLibrary_GetNumSubscribedWorkshopItems()
	{
		struct AdvancedSteamWorkshopLibrary_eventGetNumSubscribedWorkshopItems_Parms
		{
			int32 NumberOfItems;
		};
		UObject* Outer=Z_Construct_UClass_UAdvancedSteamWorkshopLibrary();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("GetNumSubscribedWorkshopItems"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04422401, 65535, sizeof(AdvancedSteamWorkshopLibrary_eventGetNumSubscribedWorkshopItems_Parms));
			UProperty* NewProp_NumberOfItems = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("NumberOfItems"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(CPP_PROPERTY_BASE(NumberOfItems, AdvancedSteamWorkshopLibrary_eventGetNumSubscribedWorkshopItems_Parms), 0x0010000000000180);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Online|AdvancedSteamWorkshop"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UAdvancedSteamWorkshopLibrary_GetSubscribedWorkshopItems()
	{
		struct AdvancedSteamWorkshopLibrary_eventGetSubscribedWorkshopItems_Parms
		{
			int32 NumberOfItems;
			TArray<FBPSteamWorkshopID> ReturnValue;
		};
		UObject* Outer=Z_Construct_UClass_UAdvancedSteamWorkshopLibrary();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("GetSubscribedWorkshopItems"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04422401, 65535, sizeof(AdvancedSteamWorkshopLibrary_eventGetSubscribedWorkshopItems_Parms));
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UArrayProperty(CPP_PROPERTY_BASE(ReturnValue, AdvancedSteamWorkshopLibrary_eventGetSubscribedWorkshopItems_Parms), 0x0010000000000580);
			UProperty* NewProp_ReturnValue_Inner = new(EC_InternalUseOnlyConstructor, NewProp_ReturnValue, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000, Z_Construct_UScriptStruct_FBPSteamWorkshopID());
			UProperty* NewProp_NumberOfItems = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("NumberOfItems"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(CPP_PROPERTY_BASE(NumberOfItems, AdvancedSteamWorkshopLibrary_eventGetSubscribedWorkshopItems_Parms), 0x0010000000000180);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Online|AdvancedSteamWorkshop"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("Returns IDs for subscribed workshop items, TArray length dictates how many"));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UAdvancedSteamWorkshopLibrary_NoRegister()
	{
		return UAdvancedSteamWorkshopLibrary::StaticClass();
	}
	UClass* Z_Construct_UClass_UAdvancedSteamWorkshopLibrary()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UBlueprintFunctionLibrary();
			Z_Construct_UPackage__Script_AdvancedSteamSessions();
			OuterClass = UAdvancedSteamWorkshopLibrary::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20000080;

				OuterClass->LinkChild(Z_Construct_UFunction_UAdvancedSteamWorkshopLibrary_GetNumSubscribedWorkshopItems());
				OuterClass->LinkChild(Z_Construct_UFunction_UAdvancedSteamWorkshopLibrary_GetSubscribedWorkshopItems());

				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UAdvancedSteamWorkshopLibrary_GetNumSubscribedWorkshopItems(), "GetNumSubscribedWorkshopItems"); // 971270678
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UAdvancedSteamWorkshopLibrary_GetSubscribedWorkshopItems(), "GetSubscribedWorkshopItems"); // 268118623
				static TCppClassTypeInfo<TCppClassTypeTraits<UAdvancedSteamWorkshopLibrary> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("AdvancedSteamWorkshopLibrary.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Classes/AdvancedSteamWorkshopLibrary.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAdvancedSteamWorkshopLibrary, 3859378460);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAdvancedSteamWorkshopLibrary(Z_Construct_UClass_UAdvancedSteamWorkshopLibrary, &UAdvancedSteamWorkshopLibrary::StaticClass, TEXT("/Script/AdvancedSteamSessions"), TEXT("UAdvancedSteamWorkshopLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAdvancedSteamWorkshopLibrary);
	UFunction* Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature()
	{
		struct _Script_AdvancedSteamSessions_eventBlueprintWorkshopDetailsDelegate_Parms
		{
			FBPSteamWorkshopItemDetails WorkShopDetails;
		};
		UObject* Outer=Z_Construct_UPackage__Script_AdvancedSteamSessions();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("BlueprintWorkshopDetailsDelegate__DelegateSignature"), RF_Public|RF_Transient|RF_MarkAsNative) UDelegateFunction(FObjectInitializer(), NULL, 0x00130000, 65535, sizeof(_Script_AdvancedSteamSessions_eventBlueprintWorkshopDetailsDelegate_Parms));
			UProperty* NewProp_WorkShopDetails = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("WorkShopDetails"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(WorkShopDetails, _Script_AdvancedSteamSessions_eventBlueprintWorkshopDetailsDelegate_Parms), 0x0010000008000182, Z_Construct_UScriptStruct_FBPSteamWorkshopItemDetails());
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Classes/SteamWSRequestUGCDetailsCallbackProxy.h"));
			MetaData->SetValue(NewProp_WorkShopDetails, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	void USteamWSRequestUGCDetailsCallbackProxy::StaticRegisterNativesUSteamWSRequestUGCDetailsCallbackProxy()
	{
		UClass* Class = USteamWSRequestUGCDetailsCallbackProxy::StaticClass();
		static const TNameNativePtrPair<ANSICHAR> AnsiFuncs[] = {
			{ "GetWorkshopItemDetails", (Native)&USteamWSRequestUGCDetailsCallbackProxy::execGetWorkshopItemDetails },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, AnsiFuncs, 1);
	}
	UFunction* Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails()
	{
		struct SteamWSRequestUGCDetailsCallbackProxy_eventGetWorkshopItemDetails_Parms
		{
			UObject* WorldContextObject;
			FBPSteamWorkshopID WorkShopID;
			int32 NumSecondsBeforeTimeout;
			USteamWSRequestUGCDetailsCallbackProxy* ReturnValue;
		};
		UObject* Outer=Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("GetWorkshopItemDetails"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04022401, 65535, sizeof(SteamWSRequestUGCDetailsCallbackProxy_eventGetWorkshopItemDetails_Parms));
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(ReturnValue, SteamWSRequestUGCDetailsCallbackProxy_eventGetWorkshopItemDetails_Parms), 0x0010000000000580, Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_NoRegister());
			UProperty* NewProp_NumSecondsBeforeTimeout = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("NumSecondsBeforeTimeout"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(CPP_PROPERTY_BASE(NumSecondsBeforeTimeout, SteamWSRequestUGCDetailsCallbackProxy_eventGetWorkshopItemDetails_Parms), 0x0010000000000080);
			UProperty* NewProp_WorkShopID = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("WorkShopID"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(WorkShopID, SteamWSRequestUGCDetailsCallbackProxy_eventGetWorkshopItemDetails_Parms), 0x0010000000000080, Z_Construct_UScriptStruct_FBPSteamWorkshopID());
			UProperty* NewProp_WorldContextObject = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("WorldContextObject"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(WorldContextObject, SteamWSRequestUGCDetailsCallbackProxy_eventGetWorkshopItemDetails_Parms), 0x0010000000000080, Z_Construct_UClass_UObject_NoRegister());
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("BlueprintInternalUseOnly"), TEXT("true"));
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Online|AdvancedSteamWorkshop"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Classes/SteamWSRequestUGCDetailsCallbackProxy.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("Ends the current session"));
			MetaData->SetValue(ReturnFunction, TEXT("WorldContext"), TEXT("WorldContextObject"));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_NoRegister()
	{
		return USteamWSRequestUGCDetailsCallbackProxy::StaticClass();
	}
	UClass* Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UOnlineBlueprintCallProxyBase();
			Z_Construct_UPackage__Script_AdvancedSteamSessions();
			OuterClass = USteamWSRequestUGCDetailsCallbackProxy::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20880080;

				OuterClass->LinkChild(Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails());

PRAGMA_DISABLE_DEPRECATION_WARNINGS
				UProperty* NewProp_OnFailure = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("OnFailure"), RF_Public|RF_Transient|RF_MarkAsNative) UMulticastDelegateProperty(CPP_PROPERTY_BASE(OnFailure, USteamWSRequestUGCDetailsCallbackProxy), 0x0010000010080000, Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature());
				UProperty* NewProp_OnSuccess = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("OnSuccess"), RF_Public|RF_Transient|RF_MarkAsNative) UMulticastDelegateProperty(CPP_PROPERTY_BASE(OnSuccess, USteamWSRequestUGCDetailsCallbackProxy), 0x0010000010080000, Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature());
PRAGMA_ENABLE_DEPRECATION_WARNINGS
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails(), "GetWorkshopItemDetails"); // 3031497421
				static TCppClassTypeInfo<TCppClassTypeTraits<USteamWSRequestUGCDetailsCallbackProxy> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("SteamWSRequestUGCDetailsCallbackProxy.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Classes/SteamWSRequestUGCDetailsCallbackProxy.h"));
				MetaData->SetValue(NewProp_OnFailure, TEXT("ModuleRelativePath"), TEXT("Classes/SteamWSRequestUGCDetailsCallbackProxy.h"));
				MetaData->SetValue(NewProp_OnFailure, TEXT("ToolTip"), TEXT("Called when there is an unsuccessful results return"));
				MetaData->SetValue(NewProp_OnSuccess, TEXT("ModuleRelativePath"), TEXT("Classes/SteamWSRequestUGCDetailsCallbackProxy.h"));
				MetaData->SetValue(NewProp_OnSuccess, TEXT("ToolTip"), TEXT("Called when there is a successful results return"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(USteamWSRequestUGCDetailsCallbackProxy, 1944480378);
	static FCompiledInDefer Z_CompiledInDefer_UClass_USteamWSRequestUGCDetailsCallbackProxy(Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy, &USteamWSRequestUGCDetailsCallbackProxy::StaticClass, TEXT("/Script/AdvancedSteamSessions"), TEXT("USteamWSRequestUGCDetailsCallbackProxy"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USteamWSRequestUGCDetailsCallbackProxy);
	UPackage* Z_Construct_UPackage__Script_AdvancedSteamSessions()
	{
		static UPackage* ReturnPackage = nullptr;
		if (!ReturnPackage)
		{
			ReturnPackage = CastChecked<UPackage>(StaticFindObjectFast(UPackage::StaticClass(), nullptr, FName(TEXT("/Script/AdvancedSteamSessions")), false, false));
			ReturnPackage->SetPackageFlags(PKG_CompiledIn | 0x00000000);
			FGuid Guid;
			Guid.A = 0x8B046F21;
			Guid.B = 0x773B66F9;
			Guid.C = 0x00000000;
			Guid.D = 0x00000000;
			ReturnPackage->SetGuid(Guid);

			Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature();
		}
		return ReturnPackage;
	}
#endif
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
PRAGMA_ENABLE_OPTIMIZATION
