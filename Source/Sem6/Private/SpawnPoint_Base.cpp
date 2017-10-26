// YangIsAwesome

#include "SpawnPoint_Base.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Character_Base.h"
#include "MyPlayerStart_Base.h"
#include "PlayerController_Base.h"
#include "PlayerState_Base.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ASpawnPoint_Base::ASpawnPoint_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	/*Root Comp*/
	MyRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = MyRootComp;
	/*-----------------------*/
	/*Mesh Setup*/
	BoxHolder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxHolder"));
	BoxHolder->SetMobility(EComponentMobility::Movable);
	BoxHolder->SetupAttachment(RootComponent);

	BoxHolder->SetIsReplicated(true);
	BoxHolder->SetSimulatePhysics(false);
	BoxHolder->bCastDynamicShadow = false;

	BoxHolder->SetMaterial(0,StoredMaterial);

	BoxHolder->bReceivesDecals = false;
	BoxHolder->SetCollisionObjectType(ECC_WorldStatic);
	BoxHolder->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxHolder->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxHolder->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECR_Ignore);
	BoxHolder->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECR_Ignore);
	BoxHolder->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel5, ECR_Ignore);
	BoxHolder->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECR_Ignore);
	BoxHolder->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel6, ECR_Ignore);
	/*--------------------------------------------------------*/
	/*Setup Collision*/
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	BoxComponent->SetMobility(EComponentMobility::Movable);
	BoxComponent->SetupAttachment(BoxHolder);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASpawnPoint_Base::OnCollisionOverlapped);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ASpawnPoint_Base::OnCollisionEndOverlaped);
	/*--------------------------------------------------------*/

	/*Setup Location to SNap to*/
	BoxHolderLocation1 = CreateDefaultSubobject<USceneComponent>(TEXT("BoxHolderLocation1"));
	BoxHolderLocation1->SetupAttachment(RootComponent);

	BoxHolderLocation2 = CreateDefaultSubobject<USceneComponent>(TEXT("BoxHolderLocation2"));
	BoxHolderLocation2->SetupAttachment(RootComponent);

	BoxHolderLocation3 = CreateDefaultSubobject<USceneComponent>(TEXT("BoxHolderLocation3"));
	BoxHolderLocation3->SetupAttachment(RootComponent);

	BoxHolderLocation4 = CreateDefaultSubobject<USceneComponent>(TEXT("BoxHolderLocation4"));
	BoxHolderLocation4->SetupAttachment(RootComponent);

	ResetBoxHolderLocation();
	ResetOccupiedBox();
	/*--------------------------------------------------------*/
}

void ASpawnPoint_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(ASpawnPoint_Base, MyOwner, COND_None);
	DOREPLIFETIME_CONDITION(ASpawnPoint_Base, BoxHolder, COND_None);
}

// Called when the game starts or when spawned
void ASpawnPoint_Base::BeginPlay()
{
	Super::BeginPlay();
	SetupComponents();
	BeginPlayNativeEvent();
}

void ASpawnPoint_Base::OnCollisionOverlapped(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter_Base* PlayerCharacter = Cast<ACharacter_Base>(OtherActor);	
	AMyPlayerStart_Base* PStart = Cast<AMyPlayerStart_Base>(MyOwner);
	APlayerState_Base* PState;
	if (PlayerCharacter && PStart)
	{
		if (PlayerCharacter->GetMyPlayerController()) 
		{
			PState = Cast<APlayerState_Base>(PlayerCharacter->GetMyPlayerController()->PlayerState);
			if (PState)
			{
				if (PState->GetSpawnLocation() == this)
					PlayerCharacter->SetIsAtBoxLocation(true);
			}
		}
	}
}

void ASpawnPoint_Base::OnCollisionEndOverlaped(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	ACharacter_Base* PlayerCharacter = Cast<ACharacter_Base>(OtherActor);
	if (PlayerCharacter)
	{
		//TODO check if it's player's base
		PlayerCharacter->SetIsAtBoxLocation(false);
	}
}

void ASpawnPoint_Base::BeginPlayNativeEvent_Implementation()
{
}

void ASpawnPoint_Base::OnRep_MyOwner()
{
}

void ASpawnPoint_Base::OnRep_BoxHolder()
{

}

UStaticMeshComponent * ASpawnPoint_Base::GetMainMesh()
{
	if (BoxHolder != nullptr) 
	{
		return BoxHolder;
	}
	return nullptr;

}

// Called every frame
void ASpawnPoint_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnPoint_Base::SnapBoxToTarget(ACharacter* Player, AActor* Box)
{
	if (BoxHolderLocation.Num() <= 0)
		return;

	USceneComponent* ShortestDistance = BoxHolderLocation[0];
	float ShortestDistanceSq = (Player->GetActorLocation() - ShortestDistance->GetComponentLocation()).SizeSquared();
	for (int BoxHolderIndex = 0; BoxHolderIndex < BoxHolderLocation.Num(); BoxHolderIndex++)
	{
		if ((Player->GetActorLocation() - BoxHolderLocation[BoxHolderIndex]->GetComponentLocation()).SizeSquared() < ShortestDistanceSq)
		{
			ShortestDistance = BoxHolderLocation[BoxHolderIndex];
		}
	}
	BoxHolderLocation.Remove(ShortestDistance);
	OccupiedBox.Add(Cast<AMyBox>(Box));
	SnapTargetToBoxHolderLocation(Box,ShortestDistance);
}

int ASpawnPoint_Base::GetNumOfBox()
{
	int NumberOfBoxes = 0;
	if (OccupiedBox.Num() <= 0)
	{
		return 0;
	}

	NumberOfBoxes = OccupiedBox.Num();
	return NumberOfBoxes;
}

void ASpawnPoint_Base::DestroyBox()
{
	int NumberOfBoxes = GetNumOfBox();
	if (NumberOfBoxes <= 0) 
	{
		return;
	}
	for (int x = 0; x < NumberOfBoxes; ++x)
	{
		if (!OccupiedBox[x]->IsPendingKill())
		{
			OccupiedBox[x]->Destroy();
		}
	}

	ResetOccupiedBox();
	ResetBoxHolderLocation();
	return;
}

void ASpawnPoint_Base::SetMyOwner(AActor * SetOwner)
{
	if (Role < ROLE_Authority) 
	{
		SERVER_SetMyOwner(SetOwner);
		return;
	}
	MyOwner = SetOwner;
}

void ASpawnPoint_Base::SERVER_SetMyOwner_Implementation(AActor * SetOwner)
{
	SetMyOwner(SetOwner);
}

bool ASpawnPoint_Base::SERVER_SetMyOwner_Validate(AActor * SetOwner)
{
	return true;
}

void ASpawnPoint_Base::SnapTargetToBoxHolderLocation(AActor * ItemToSnapTo, USceneComponent * ItemToSnapAt)
{
	ItemToSnapTo->AttachToComponent(ItemToSnapAt, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void ASpawnPoint_Base::ResetBoxHolderLocation()
{
	BoxHolderLocation.Empty();

	BoxHolderLocation.Add(BoxHolderLocation1);
	BoxHolderLocation.Add(BoxHolderLocation2);
	BoxHolderLocation.Add(BoxHolderLocation3);
	BoxHolderLocation.Add(BoxHolderLocation4);
}

void ASpawnPoint_Base::ResetOccupiedBox()
{
	OccupiedBox.Empty();
}

void ASpawnPoint_Base::SetupComponents()
{
	ResetOccupiedBox();
	ResetBoxHolderLocation();
}

