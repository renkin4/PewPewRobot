// YangIsAwesome

#include "Weapon_Base.h"
#include "MyBlueprintFunctionLibrary.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AWeapon_Base::AWeapon_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponType = EWeaponType::WT_MachineGun;
	WeaponFireType = EWeaponFireType::WT_InstantHit;
	bReplicates = true;

	ShowFireLine = false;
}

// Called when the game starts or when spawned
void AWeapon_Base::BeginPlay()
{
	Super::BeginPlay();
	GetComponents<UStaticMeshComponent>(StaticMeshComp);
	
}

// Called every frame
void AWeapon_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ELootAbleType AWeapon_Base::GetLootableType_Implementation()
{
	return LootableType;
}

EWeaponType AWeapon_Base::GetWeaponType_Implementation()
{
	return WeaponType;
}

void AWeapon_Base::FireWeapon()
{
	RayCastFromMiddle();
	//TODO Simulate Particle and sound
	//TODO Set EditAnywhere for Particle And sound
}

void AWeapon_Base::SetPawnOwner(AController* Controller)
{
	PawnOwner = Controller;
	return;
}

FVector2D AWeapon_Base::GetScreenLocation()
{
	APlayerController_Base* PlayerOwner = Cast<APlayerController_Base>(PawnOwner);
	int32 ViewportY;
	int32 ViewportX;

	if (PlayerOwner) 
	{
		PlayerOwner->GetViewportSize(ViewportX, ViewportY);
		return FVector2D(ViewportX, ViewportY);
	}
	return FVector2D(0.0f, 0.0f);
}

void AWeapon_Base::RayCastFromMiddle()
{
	switch (WeaponFireType)
	{
	case EWeaponFireType::WT_None:
		break;
	case EWeaponFireType::WT_ProjecTile:
		break;
	case EWeaponFireType::WT_InstantHit:
		InstantHitFire();
		break;
	default:
		break;
	}
}

void AWeapon_Base::InstantHitFire()
{
	//TODO Mini Stun Ability
	FHitResult HitScreenData(ForceInit);
	FHitResult HitData(ForceInit);
	FHitResult DamageInfo(ForceInit);
	APlayerController_Base* PlayerOwner = Cast<APlayerController_Base>(PawnOwner);
	FVector WorldPosition;
	FVector WorldDirection;
	if (PlayerOwner)
	{
		PlayerOwner->DeprojectScreenPositionToWorld(GetScreenLocation().X*0.5f, GetScreenLocation().Y*0.5f, WorldPosition, WorldDirection);
		FVector StartPoint;
		FVector EndPoint;

		if (PlayerOwner->GetIsAiming())
		{
			StartPoint = WorldPosition;
			EndPoint = WorldPosition + (WorldDirection * 5000);
			FVector ShootStartPoint = StaticMeshComp[0]->GetSocketLocation("ShootingPoint");
			FVector ShootEndPoint;
			UMyBlueprintFunctionLibrary::Trace(GetWorld(), this, StartPoint, EndPoint, HitScreenData, ECC_Visibility, false);

			ShootEndPoint = HitScreenData.bBlockingHit ? HitScreenData.ImpactPoint : WorldPosition + (WorldDirection * 5000);
			//TODO set Server Notify 
			//Trace From Gun
			if (UMyBlueprintFunctionLibrary::Trace(GetWorld(), this, ShootStartPoint, ShootEndPoint, HitData, ECC_Visibility, false))
			{
				//TODO check if it's player // AI deal damage to them
				//Null UDamageType
				TSubclassOf<UDamageType> P;
				UGameplayStatics::ApplyPointDamage(HitData.Actor.Get(), 1.0f, HitData.ImpactNormal, DamageInfo, PawnOwner, this, P);
				/*Debug*/
				//TODO refactor to Debug Line Function
				DrawDebugSolidBox(GetWorld(), ShootEndPoint, FVector(10.0f, 10.0f, 5.0f), FColor::Red, false, 0.5f, 0);
			}
			/*Debug*/
			DebugLine(ShootStartPoint, ShootEndPoint, FColor::Green);
		}
		else
		{
			StartPoint = StaticMeshComp[0]->GetSocketLocation("ShootingPoint");
			EndPoint = StaticMeshComp[0]->GetSocketLocation("ShootingPoint") + (2000 * UKismetMathLibrary::GetForwardVector(StaticMeshComp[0]->GetSocketRotation("ShootingPoint")));
			//Without Aiming
			if (UMyBlueprintFunctionLibrary::Trace(GetWorld(), this, StartPoint, EndPoint, HitData, ECC_Visibility, false))
			{
				TSubclassOf<UDamageType> P;
				UGameplayStatics::ApplyPointDamage(HitData.Actor.Get(), 1.0f, HitData.ImpactNormal, DamageInfo, PawnOwner, this, P);
				EndPoint = HitData.ImpactPoint;
				DrawDebugSolidBox(GetWorld(), EndPoint, FVector(10.0f, 10.0f, 5.0f), FColor::Red, false, 0.5f, 0);
			}
			/*Debug*/
			DebugLine(StartPoint, EndPoint, FColor::Green);
		}
	}
}

void AWeapon_Base::DebugLine(FVector Start, FVector End, FColor Color)
{
	//TODO set enum and check from Bool
	if (ShowFireLine) 
	{
		DrawDebugLine(GetWorld(), Start, End, Color, false, 1.0f, 0, 1.0f);
	}
}

