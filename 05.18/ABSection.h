// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "ABSection.generated.h"

UCLASS()
class UNREALCPP_0309_API AABSection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABSection();
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	enum class ESectionState : uint8
	{
		READY = 0,
		BATTLE,
		COMPLETE
	};

	void SetState(ESectionState NewState);
	ESectionState CurrentState = ESectionState::READY;

	void OperateGates(bool bOpen = true);

	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherCom, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnNPCSpawn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh, Meta = (AllowPrivateAccess = true))
	TArray<UStaticMeshComponent*> GateMeshes;

	UPROPERTY(VisibleAnywhere, Category = Trigger, Meta = (AllowPrivateAccess = true))
	TArray<UBoxComponent*> GateTriggers; //게이트에 붙는 트리거들

	//레벨별 구분위한 땅 메시
	UPROPERTY(VisibleAnywhere, Category = Mesh, Meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;

	//문마다 붙어있는 트리거
	UPROPERTY(VisibleAnywhere, Category = Trigger, Meta = (AllowPrivateAccess = true))
	UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, Category = State, Meta = (AllowPrivateAccess = true))
	bool bNoBattle;

	UPROPERTY(EditAnywhere, Category = State, Meta = (AllowPrivateAccess = true))
	float EnemySpawnTime;

	UPROPERTY(EditAnywhere, Category = State, Meta = (AllowPrivateAccess = true))
	float ItemBoxSpawnTime;

	FTimerHandle SpawnNPCTimerHander = {};
	FTimerHandle SpawnItemBoxTimerHandle = {};
};
