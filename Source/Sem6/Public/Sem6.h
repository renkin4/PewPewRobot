// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSem6, Log, All);

#define print(text) if (GEngine) UKismetSystemLibrary::PrintString(GetWorld(), text, true, true, FColor::Magenta, 10.0f)
