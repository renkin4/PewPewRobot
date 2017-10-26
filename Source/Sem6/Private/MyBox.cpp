// YangIsAwesome

#include "MyBox.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"


// Sets default values
AMyBox::AMyBox(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bReplicateMovement = true;

	MyBoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	
	MyBoxMesh->SetSimulatePhysics(true);
	MyBoxMesh->bCastDynamicShadow = false;
	
	MyBoxMesh->bReceivesDecals = false;
	MyBoxMesh->SetCollisionObjectType(ECC_WorldStatic);
	MyBoxMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MyBoxMesh->SetCollisionResponseToAllChannels(ECR_Block);
	MyBoxMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECR_Ignore);
	MyBoxMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Ignore);
	MyBoxMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECR_Ignore);
	MyBoxMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel5, ECR_Ignore);
	MyBoxMesh->CustomDepthStencilValue = 1;

}

// Called when the game starts or when spawned
void AMyBox::BeginPlay()
{
	Super::BeginPlay();
}

ELootAbleType AMyBox::GetLootableType_Implementation()
{
	return LootableType;
}

EWeaponType AMyBox::GetWeaponType_Implementation()
{
	return EWeaponType::WT_None;
}

void AMyBox::HighLightActor_Implementation()
{
	MyBoxMesh->SetRenderCustomDepth(true);
	GetWorldTimerManager().SetTimer(TurnOffRenderCustomDepthHandle, this, &AMyBox::TurnOffCustomDepth, 0.1f, false);
}

void AMyBox::TurnOffCustomDepth()
{
	MyBoxMesh->SetRenderCustomDepth(false);
}

// Called every frame
void AMyBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AMyBox::bSetSimulatePhysic(bool bShouldSimulate)
{
	MyBoxMesh->SetSimulatePhysics(bShouldSimulate);
	return bShouldSimulate;
}

UStaticMeshComponent * AMyBox::GetStaticMesh()
{
	return MyBoxMesh;
}

