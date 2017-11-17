// YangIsAwesome

#include "Projectile_Base.h"


// Sets default values
AProjectile_Base::AProjectile_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AProjectile_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile_Base::SetHommingMissle_Implementation(AActor * TargettedActor)
{
}

