#include "Unreal.h"






SDK::UConsole* Unreal::Console::Get()
{
	SDK::UGameViewportClient* GameViewportClient = GameViewportClient::Get();
	if (GameViewportClient == nullptr || GameViewportClient->ViewportConsole == nullptr)
		return nullptr;

	return GameViewportClient->ViewportConsole;
}

bool Unreal::Console::Construct(const bool& ignorePresence)
{
	SDK::UGameViewportClient* GameViewportClient = GameViewportClient::Get();
	if (GameViewportClient == nullptr)
		return false;

	if (ignorePresence == false && GameViewportClient->ViewportConsole) // If presence shouldn't be ignored, we're looking up if Console already exist.
		return false;

	/*
		If Engine is present, the Console Class defined in it will be used.
		Otherwise, the default Console Class will serve as a fallback.

		Before assigning Console to the Game Viewport Client, ensure that SpawnObject() returned a valid pointer.
	*/
	SDK::UEngine* Engine = Engine::Get();
	if (SDK::UObject* objectReference = SDK::UGameplayStatics::SpawnObject(Engine ? Engine->ConsoleClass : SDK::TSubclassOf<SDK::UConsole>(SDK::UConsole::StaticClass()), GameViewportClient))
	{
		GameViewportClient->ViewportConsole = static_cast<SDK::UConsole*>(objectReference); // Clarify that newly spawned Object is of class Console.

		/* Fill empty history buffer with set of general console commands. */
		if (GameViewportClient->ViewportConsole->HistoryBuffer.Num() == 0)
		{
			GameViewportClient->ViewportConsole->HistoryBuffer = SDK::UKismetStringLibrary::ParseIntoArray(L"stat FPS | stat Unit | stat UnitGraph | stat UnitMax | stat Summary | stat Hitches | stat AI & stat Levels & stat ColorList & PrevViewMode & ViewMode Lit", L" & ", true);
		}

		return true;
	}
	else
		return false;
}


bool Unreal::Console::Print(const std::wstring& wString)
{
	const wchar_t* wcString = wString.c_str();
	wprintf(L"%ls\n", wcString); // Print to std::cout (if present).

	if (SDK::APlayerController* playerController = PlayerController::Get())
	{
		playerController->ClientMessage(SDK::FString(wcString), SDK::UKismetStringLibrary::Conv_StringToName(L"None"), 0);
		return true;
	}
	else
		return false;
}
bool Unreal::Console::Print(const std::string& string)
{
	return Print(std::wstring(string.begin(), string.end()));
}

bool Unreal::Console::Print(const int32_t& integer)
{
	return Print(std::to_wstring(integer));
}
bool Unreal::Console::Print(const uint32_t& unsignedInteger)
{
	return Print(std::to_wstring(unsignedInteger));
}

bool Unreal::Console::Print(const SDK::FVector& vector)
{
	return Print(SDK::UKismetStringLibrary::Conv_VectorToString(vector).ToWString());
}
bool Unreal::Console::Print(const SDK::FRotator& rotator)
{
	return Print(SDK::UKismetStringLibrary::Conv_RotatorToString(rotator).ToWString());
}

bool Unreal::Console::Print(SDK::UObject* objectReference)
{
	return Print(SDK::UKismetStringLibrary::Conv_ObjectToString(objectReference).ToWString());
}

bool Unreal::Console::Print()
{
	return Print(L" ");
}


bool Unreal::Console::Clear()
{
	static const std::wstring emptyLines = L" \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n ";
	return Print(emptyLines);
}

bool Unreal::Console::ExecuteConsoleCommand(const std::wstring& command)
{
	SDK::UWorld* world = World::Get();
	if (world == nullptr)
		return false;

	SDK::UKismetSystemLibrary::ExecuteConsoleCommand(world, SDK::FString(command.c_str()), PlayerController::Get());
	return true;
}






SDK::UInputSettings* Unreal::InputSettings::Get()
{
	SDK::UInputSettings* InputSettings = SDK::UInputSettings::GetDefaultObj();
	return InputSettings ? InputSettings : nullptr;
}


bool Unreal::InputSettings::AssignConsoleBindings()
{
	SDK::UInputSettings* InputSettings = InputSettings::Get();
	if (InputSettings == nullptr)
		return false;

	int32_t bindingsNum = InputSettings->ConsoleKeys.Num();
	if (bindingsNum > 0)
		InputSettings->ConsoleKeys[0].KeyName = SDK::UKismetStringLibrary::Conv_StringToName(L"Tilde");
	if (bindingsNum > 1)
		InputSettings->ConsoleKeys[1].KeyName = SDK::UKismetStringLibrary::Conv_StringToName(L"F10");
	if (bindingsNum > 2)
		InputSettings->ConsoleKeys[2].KeyName = SDK::UKismetStringLibrary::Conv_StringToName(L"¸");

	return true;
}






SDK::UGameViewportClient* Unreal::GameViewportClient::Get()
{
	SDK::UEngine* Engine = Engine::Get();
	if (Engine == nullptr || Engine->GameViewport == nullptr)
		return nullptr;

	return Engine->GameViewport;
}






SDK::UEngine* Unreal::Engine::Get()
{
	SDK::UEngine* Engine = SDK::UEngine::GetEngine();
	return Engine ? Engine : nullptr;
}






SDK::UGameInstance* Unreal::GameInstance::Get()
{
	SDK::UWorld* world = World::Get();
	if (world == nullptr)
		return nullptr;

	SDK::UGameInstance* GameInstance = SDK::UGameplayStatics::GetGameInstance(world);
	if (GameInstance == nullptr)
		return nullptr;

	return GameInstance;
}






SDK::AGameModeBase* Unreal::GameMode::Get()
{
	SDK::UWorld* world = World::Get();
	if (world == nullptr)
		return nullptr;

	SDK::AGameModeBase* GameMode = SDK::UGameplayStatics::GetGameMode(world);
	if (GameMode == nullptr)
		return nullptr;

	return GameMode;
}







SDK::AGameStateBase* Unreal::GameState::Get()
{
	SDK::UWorld* world = World::Get();
	if (world == nullptr)
		return nullptr;

	SDK::AGameStateBase* GameState = SDK::UGameplayStatics::GetGameState(world);
	if (GameState == nullptr)
		return nullptr;

	return GameState;
}






#ifdef LEVEL_SEQUENCE
bool Unreal::Level::CreateLevelSequence(SDK::ULevelSequence* levelSequenceAsset, const float& startTime, const float& playRate, const int32_t& loopCount)
{
	SDK::UWorld* world = World::Get();
	if (world == nullptr || levelSequenceAsset == nullptr)
		return false;

	SDK::FMovieSceneSequencePlaybackSettings sequencePlaybackSettings;
	sequencePlaybackSettings.bAutoPlay = true;
	sequencePlaybackSettings.StartTime = startTime;
	sequencePlaybackSettings.PlayRate = playRate;

	SDK::FMovieSceneSequenceLoopCount sequenceLoopCount{ loopCount };
	sequencePlaybackSettings.LoopCount = sequenceLoopCount;

	SDK::ALevelSequenceActor* levelSequenceActor;
	SDK::ULevelSequencePlayer::CreateLevelSequencePlayer(world, levelSequenceAsset, sequencePlaybackSettings, &levelSequenceActor);

	return levelSequenceActor;
}

bool Unreal::Level::CreateLevelSequence_ThreadSafe(SDK::ULevelSequence* levelSequenceAsset, const float& startTime, const float& playRate, const int32_t& loopCount)
{
	__try
	{
		return CreateLevelSequence(levelSequenceAsset, startTime, playRate, loopCount);
	}
	__except (EXCEPTION())
	{
		return false;
	}
}

#ifdef SOFT_PATH
bool Unreal::Level::CreateLevelSequence(const std::wstring& levelSequencePath, const float& startTime, const float& playRate, const int32_t& loopCount)
{
	SDK::UObject* objectReference = Object::SoftLoadObject(levelSequencePath);
	bool success = false;

	if (objectReference && objectReference->IsA(SDK::ULevelSequence::StaticClass()))
	{
		SDK::ULevelSequence* levelSequenceAsset = static_cast<SDK::ULevelSequence*>(objectReference);
		success = CreateLevelSequence(levelSequenceAsset, startTime, playRate, loopCount);
	}

#ifdef SOFT_LOAD_FREEMEMORY
	World::RemoveLevelStreamingByName(Utilities::String::ToString(Unreal::Object::ShortenObjectPath(levelSequencePath)));
#endif

	return success;
}

bool Unreal::Level::CreateLevelSequence_ThreadSafe(const std::wstring& levelSequencePath, const float& startTime, const float& playRate, const int32_t& loopCount)
{
	__try
	{
		return CreateLevelSequence(levelSequencePath, startTime, playRate, loopCount);
	}
	__except (Utilities::Exception::Handle(GetExceptionInformation(), __FUNCSIG__))
	{
		return false;
	}
}
#endif
#endif






std::vector<SDK::ULevelStreaming*> Unreal::LevelStreaming::GetAll(SDK::UWorld* worldReference)
{
	std::vector<SDK::ULevelStreaming*> outCollection;

	if (worldReference == nullptr)
		return outCollection;

	if (worldReference->StreamingLevels.Num() == 0)
		return outCollection;

	for (SDK::ULevelStreaming* levelStreaming : worldReference->StreamingLevels)
	{
		if (levelStreaming == nullptr)
			continue;

		outCollection.push_back(levelStreaming);
	}

	return outCollection;
}

std::vector<SDK::ULevelStreaming*> Unreal::LevelStreaming::GetAll()
{
	return Unreal::LevelStreaming::GetAll(Unreal::World::Get());
}


std::vector<Unreal::LevelStreaming::DataStructure> Unreal::LevelStreaming::FilterByLevelPath(const std::vector<LevelStreaming::DataStructure>& levelStreamingsCollection, const std::string& filter, const bool& caseSensitive)
{
	std::vector<LevelStreaming::DataStructure> outCollection;
	size_t filterLength = filter.length();

	/* Filter Level Streamings by "Search Filter" */
	for (Unreal::LevelStreaming::DataStructure levelStreaming : levelStreamingsCollection)
	{
		/* "Search Filter" is empty - Actor considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
				matchFilters = levelStreaming.levelPath.find(filter) != std::string::npos;
			else
			{
				std::string levelPathLowerCase = levelStreaming.levelPath;
				std::string filterLowerCase = filter;

				std::transform(levelPathLowerCase.begin(), levelPathLowerCase.end(), levelPathLowerCase.begin(),
					[](unsigned char c) { return std::tolower(c); });
				std::transform(filterLowerCase.begin(), filterLowerCase.end(), filterLowerCase.begin(),
					[](unsigned char c) { return std::tolower(c); });

				matchFilters = levelPathLowerCase.find(filterLowerCase) != std::string::npos;
			}
		}

		if (matchFilters)
			outCollection.push_back(levelStreaming); // Actor is good to go, can be considered "filtered".
	}

	return outCollection;
}


#ifdef SOFT_PATH
bool Unreal::LevelStreaming::LoadLevelInstance(const std::wstring& objectPath, const SDK::FVector& locationOffset, const SDK::FRotator& rotationOffset, const bool& useInstancedName)
{
	SDK::UWorld* world = World::Get();
	if (world == nullptr)
		return false;

	bool outSuccess;

	std::wstring instancedNameOverride = std::wstring();
	if (useInstancedName)
	{
		static int instanceCounter = 0;
		/* locationOffset & rotationOffset would both be ignored when an Level Instance of same name is already present. */
		instancedNameOverride = Unreal::Object::GetObjectNameFromPath(objectPath) + L"_" + std::to_wstring(instanceCounter++);
	}

#ifdef UE5
	static SDK::TSubclassOf<SDK::ULevelStreamingDynamic> optionalLevelStreamingClass;
	SDK::ULevelStreamingDynamic::LoadLevelInstance(world, SDK::FString(objectPath.c_str()), locationOffset, rotationOffset, &outSuccess, SDK::FString(instancedNameOverride.c_str()), optionalLevelStreamingClass, false);
#else
	SDK::ULevelStreamingDynamic::LoadLevelInstance(world, SDK::FString(objectPath.c_str()), locationOffset, rotationOffset, &outSuccess, SDK::FString(instancedNameOverride.c_str()));
#endif

	return outSuccess;
}
#endif






SDK::UWorld* Unreal::World::Get()
{
	SDK::UWorld* world = SDK::UWorld::GetWorld();
	return world ? world : nullptr;
}


bool Unreal::World::RemoveLevelStreamingAtIndex(SDK::UWorld* worldReference, const int32_t& index)
{
	if (worldReference == nullptr)
		return false;

	int32_t levelStreamingsCount = worldReference->StreamingLevels.Num();
	if (levelStreamingsCount == 0 || levelStreamingsCount < index)
		return false;

	return worldReference->StreamingLevels.Remove(index);
}

bool Unreal::World::RemoveLevelStreamingAtIndex(const int32_t& index)
{
	SDK::UWorld* world = World::Get();
	if (world == nullptr)
		return false;

	return RemoveLevelStreamingAtIndex(world, index);
}


bool Unreal::World::RemoveLevelStreamingByName(SDK::UWorld* worldReference, const std::string& levelStreamingName)
{
	if (worldReference == nullptr)
		return false;

	int32_t levelStreamingsCount = worldReference->StreamingLevels.Num();
	if (levelStreamingsCount == 0)
		return false;

	for (int32_t index = 0; index < levelStreamingsCount; index++)
	{
		SDK::ULevelStreaming* levelStreaming = worldReference->StreamingLevels[index];

		if (levelStreaming != nullptr && levelStreaming->GetWorldAssetPackageFName().GetRawString() == levelStreamingName)
		{
			worldReference->StreamingLevels.Remove(index);
			return true;
		}
	}

	return false;
}

bool Unreal::World::RemoveLevelStreamingByName(const std::string& levelStreamingName)
{
	SDK::UWorld* world = World::Get();
	if (world == nullptr)
		return false;

	return RemoveLevelStreamingByName(world, levelStreamingName);
}






SDK::APawn* Unreal::Pawn::Get(const int32_t& playerIndex)
{
	SDK::UWorld* world = World::Get();
	if (world == nullptr)
		return nullptr;

	SDK::APawn* Pawn = SDK::UGameplayStatics::GetPlayerPawn(world, playerIndex);
	if (Pawn == nullptr)
		return nullptr;

	return Pawn;
}


bool Unreal::Pawn::PlayAnimationMontage(SDK::APawn* pawnReference, SDK::UAnimMontage* animationMontageAsset, const float& startAt, const float& playRate, const bool& stopAllMontages)
{
	if (pawnReference == nullptr || animationMontageAsset == nullptr)
		return false;

	SDK::UActorComponent* actorComponent = pawnReference->GetComponentByClass(SDK::USkeletalMeshComponent::StaticClass());
	if (actorComponent == nullptr)
		return false;

	SDK::USkeletalMeshComponent* skeletalMeshComponent = static_cast<SDK::USkeletalMeshComponent*>(actorComponent);
	SDK::UAnimInstance* animationInstance = skeletalMeshComponent->GetAnimInstance();
	if (animationInstance == nullptr)
		return false;

	animationInstance->Montage_Play(animationMontageAsset, playRate, SDK::EMontagePlayReturnType::MontageLength, startAt, stopAllMontages);
}

#ifdef SOFT_PATH
bool Unreal::Pawn::PlayAnimationMontage(SDK::APawn* pawnReference, const std::wstring& animationMontagePath, const float& startAt, const float& playRate, const bool& stopAllMontages)
{
	SDK::UObject* objectReference = Object::SoftLoadObject(animationMontagePath);
	bool success = false;

	if (objectReference && objectReference->IsA(SDK::UAnimMontage::StaticClass()))
	{
		SDK::UAnimMontage* animationMontageAsset = static_cast<SDK::UAnimMontage*>(objectReference);
		success = PlayAnimationMontage(pawnReference, animationMontageAsset, startAt, playRate, stopAllMontages);
	}

#ifdef SOFT_LOAD_FREEMEMORY
	World::RemoveLevelStreamingByName(Utilities::String::ToString(Unreal::Object::ShortenObjectPath(animationMontagePath)));
#endif

	return success;
}
#endif


bool Unreal::Pawn::PlayAnimation(SDK::APawn* pawnReference, SDK::UAnimationAsset* animationAsset, const bool& looping)
{
	if (pawnReference == nullptr || animationAsset == nullptr)
		return false;

	SDK::UActorComponent* actorComponent = pawnReference->GetComponentByClass(SDK::USkeletalMeshComponent::StaticClass());
	if (actorComponent == nullptr)
		return false;

	SDK::USkeletalMeshComponent* skeletalMeshComponent = static_cast<SDK::USkeletalMeshComponent*>(actorComponent);
	skeletalMeshComponent->PlayAnimation(animationAsset, looping);
	return skeletalMeshComponent->IsPlaying();
}

#ifdef SOFT_PATH
bool Unreal::Pawn::PlayAnimation(SDK::APawn* pawnReference, const std::wstring& animationPath, const bool& looping)
{
	SDK::UObject* objectReference = Object::SoftLoadObject(animationPath);
	bool success = false;

	if (objectReference && objectReference->IsA(SDK::UAnimationAsset::StaticClass()))
	{
		SDK::UAnimationAsset* animationAsset = static_cast<SDK::UAnimationAsset*>(objectReference);
		success = PlayAnimation(pawnReference, animationAsset, looping);
	}

#ifdef SOFT_LOAD_FREEMEMORY
	World::RemoveLevelStreamingByName(Utilities::String::ToString(Unreal::Object::ShortenObjectPath(animationPath)));
#endif

	return success;
}
#endif






SDK::UCheatManager* Unreal::CheatManager::Get()
{
	SDK::APlayerController* playerController = PlayerController::Get();
	if (playerController == nullptr || playerController->CheatManager == nullptr)
		return nullptr;

	return playerController->CheatManager;
}


bool Unreal::CheatManager::Construct(const bool& ignorePresence)
{
	SDK::APlayerController* playerController = PlayerController::Get();
	if (playerController == nullptr)
		return false;

	if (ignorePresence == false && playerController->CheatManager) // If presence shouldn't be ignored, we're looking up if Cheat Manager already exist.
		return false;

	if (playerController->CheatClass == nullptr) // If Player Controller has no cheating class specified, fallback to default Cheat Manager class.
		playerController->CheatClass = SDK::UCheatManager::StaticClass();

	/* Before assigning Cheat Manager to the Player Controller, ensure that SpawnObject() returned a valid pointer. */
	if (SDK::UObject* objectReference = SDK::UGameplayStatics::SpawnObject(playerController->CheatClass, playerController))
	{
		playerController->CheatManager = static_cast<SDK::UCheatManager*>(objectReference); // Clarify that newly spawned Object is of class Cheat Manager.
		return true;
	}
	else
		return false;
}


bool Unreal::CheatManager::Summon(SDK::UCheatManager* cheatManagerReference, SDK::TSubclassOf<SDK::AActor> actorClass)
{
	if (cheatManagerReference == nullptr)
		return false;

	if (actorClass == nullptr)
		return false;

	std::string className = actorClass->GetName();
	std::wstring wClassName = Utilities::String::ToWString(className);
	cheatManagerReference->Summon(SDK::FString(wClassName.c_str()));
	return true;
}

bool Unreal::CheatManager::Summon(const SDK::TSubclassOf<SDK::AActor>& actorClass)
{
	SDK::APlayerController* playerController = PlayerController::Get();
	if (playerController == nullptr)
		return false;

	SDK::UObject* objectReference = SDK::UGameplayStatics::SpawnObject(SDK::UCheatManager::StaticClass(), playerController);
	if (objectReference == nullptr)
		return false;

	return Summon(static_cast<SDK::UCheatManager*>(objectReference), actorClass);
}


#ifdef SOFT_PATH
bool Unreal::CheatManager::SoftSummon(SDK::UCheatManager* cheatManagerReference, const std::wstring& actorPath)
{
	if (cheatManagerReference == nullptr)
		return false;

	/* Ensure Soft Path is valid and Actor is loaded in to game memory, so we could spawn it later on. */
	SDK::UClass* actorClass = Unreal::Object::SoftLoadClass(actorPath);
	bool success = false;

	if (actorClass)
	{
		std::wstring actorName = Unreal::Object::GetObjectNameFromPath(actorPath);
		if (actorName.empty() == false)
		{
			cheatManagerReference->Summon(SDK::FString(actorName.c_str()));
			success = true;
		}
	}

#ifdef SOFT_LOAD_FREEMEMORY
	World::RemoveLevelStreamingByName(Utilities::String::ToString(Unreal::Object::ShortenObjectPath(actorPath)));
#endif

	return success;
}

bool Unreal::CheatManager::SoftSummon(const std::wstring& actorPath)
{
	SDK::APlayerController* playerController = PlayerController::Get();
	if (playerController == nullptr)
		return false;

	SDK::UObject* objectReference = SDK::UGameplayStatics::SpawnObject(SDK::UCheatManager::StaticClass(), playerController);
	if (objectReference == nullptr)
		return false;

	return SoftSummon(static_cast<SDK::UCheatManager*>(objectReference), actorPath);
}
#endif






SDK::APlayerController* Unreal::PlayerController::Get(const int32_t& playerIndex)
{
	SDK::UWorld* world = World::Get();
	if (world == nullptr)
		return nullptr;

	SDK::APlayerController* PlayerController = SDK::UGameplayStatics::GetPlayerController(world, playerIndex);
	if (PlayerController == nullptr)
		return nullptr;

	return PlayerController;
}


SDK::FVector Unreal::PlayerController::GetLocation(SDK::APlayerController* playerControllerReference)
{
	if (playerControllerReference == nullptr)
		return SDK::FVector();

	if (playerControllerReference->AcknowledgedPawn)
		return Unreal::Actor::GetLocation(playerControllerReference->AcknowledgedPawn);
	else if (playerControllerReference->PlayerCameraManager)
		return Unreal::Actor::GetLocation(playerControllerReference->PlayerCameraManager);
	else
		return SDK::FVector();
}

SDK::FVector Unreal::PlayerController::GetLocation(const int32_t& playerIndex)
{
	SDK::APlayerController* playerController = PlayerController::Get(playerIndex);
	return Unreal::PlayerController::GetLocation(playerController);
}

SDK::FRotator Unreal::PlayerController::GetRotation(SDK::APlayerController* playerControllerReference)
{
	if (playerControllerReference == nullptr)
		return SDK::FRotator();

	if (playerControllerReference->AcknowledgedPawn)
		return Unreal::Actor::GetRotation(playerControllerReference->AcknowledgedPawn);
	else if (playerControllerReference->PlayerCameraManager)
		return Unreal::Actor::GetRotation(playerControllerReference->PlayerCameraManager);
	else
		return SDK::FRotator();
}

SDK::FRotator Unreal::PlayerController::GetRotation(const int32_t& playerIndex)
{
	SDK::APlayerController* playerController = PlayerController::Get(playerIndex);
	return Unreal::PlayerController::GetRotation(playerController);
}

SDK::FVector Unreal::PlayerController::GetScale3D(SDK::APlayerController* playerControllerReference)
{
	if (playerControllerReference == nullptr)
		return SDK::FVector();

	if (playerControllerReference->AcknowledgedPawn)
		return Unreal::Actor::GetScale3D(playerControllerReference->AcknowledgedPawn);
	else if (playerControllerReference->PlayerCameraManager)
		return Unreal::Actor::GetScale3D(playerControllerReference->PlayerCameraManager);
	else
		return SDK::FVector();
}

SDK::FVector Unreal::PlayerController::GetScale3D(const int32_t& playerIndex)
{
	SDK::APlayerController* playerController = PlayerController::Get(playerIndex);
	return Unreal::PlayerController::GetScale3D(playerController);
}

Unreal::Transform Unreal::PlayerController::GetTransform(SDK::APlayerController* playerControllerReference)
{
	if (playerControllerReference == nullptr)
		return Unreal::Transform();

	if (playerControllerReference->AcknowledgedPawn)
		return Unreal::Actor::GetTransform(playerControllerReference->AcknowledgedPawn);
	else if (playerControllerReference->PlayerCameraManager)
		return Unreal::Actor::GetTransform(playerControllerReference->PlayerCameraManager);
	else
		return Unreal::Transform();
}

Unreal::Transform Unreal::PlayerController::GetTransform(const int32_t& playerIndex)
{
	SDK::APlayerController* playerController = PlayerController::Get(playerIndex);
	return Unreal::PlayerController::GetTransform(playerController);
}


void Unreal::PlayerController::SetViewTarget(SDK::AActor* actorReference, const SDK::EViewTargetBlendFunction& blendFunction, const float& blendTime, const float& blendExponent)
{
	if (actorReference == nullptr)
		return;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return;

	playerController->SetViewTargetWithBlend(actorReference, blendTime, blendFunction, blendExponent, false);
}

void Unreal::PlayerController::SetViewTarget(SDK::AActor* actorReference)
{
	SetViewTarget(actorReference, SDK::EViewTargetBlendFunction::VTBlend_Linear, 0.0f, 0.0f);
}






SDK::ACharacter* Unreal::Character::Get(const int32_t& playerIndex)
{
	SDK::UWorld* world = World::Get();
	if (world == nullptr)
		return nullptr;

	SDK::ACharacter* Character = SDK::UGameplayStatics::GetPlayerCharacter(world, playerIndex);
	if (Character == nullptr)
		return nullptr;

	return Character;
}


bool Unreal::Character::Jump(SDK::ACharacter* characterReference)
{
	if (characterReference == nullptr)
		return false;

	bool canJump = characterReference->CanJump();
	if (canJump)
		characterReference->Jump();

	return canJump;
}
bool Unreal::Character::Jump(const int32_t& playerIndex)
{
	SDK::ACharacter* Character = Character::Get(playerIndex);

	if (Character == nullptr)
		return false;

	bool canJump = Character->CanJump();
	if (canJump)
		Character->Jump();

	return canJump;
}


bool Unreal::Character::LocalLaunch(SDK::ACharacter* characterReference, const SDK::FVector& launchVelocity, const bool& overrideHorizontalVelocity, const bool& overrideVerticalVelocity)
{
	if (characterReference == nullptr || characterReference->CharacterMovement == nullptr
									  || characterReference->CharacterMovement->bCheatFlying
									  || characterReference->CharacterMovement->MovementMode == SDK::EMovementMode::MOVE_None
									  || characterReference->CharacterMovement->IsActive() == false)
		return false;

	SDK::FVector finalVelocity = launchVelocity;
	const SDK::FVector characterVelocity = characterReference->GetVelocity();

	if (overrideHorizontalVelocity == false)
	{
		finalVelocity.X += characterVelocity.X;
		finalVelocity.Y += characterVelocity.Y;
	}

	if (overrideVerticalVelocity == false)
	{
		finalVelocity.Z += characterVelocity.Z;
	}

	characterReference->CharacterMovement->PendingLaunchVelocity = finalVelocity;
	characterReference->OnLaunched(finalVelocity, overrideHorizontalVelocity, overrideVerticalVelocity);

	if (characterReference->CharacterMovement->bCheatFlying)
	{
		characterReference->SetActorEnableCollision(true);
		characterReference->CharacterMovement->bCheatFlying = false;
		characterReference->CharacterMovement->SetMovementMode(SDK::EMovementMode::MOVE_Walking, 0);
	}

	return true;
}
bool Unreal::Character::LocalLaunch(const int32_t& playerIndex, const SDK::FVector& launchVelocity, const bool& overrideHorizontalVelocity, const bool& overrideVerticalVelocity)
{
	return LocalLaunch(Character::Get(playerIndex), launchVelocity, overrideHorizontalVelocity, overrideVerticalVelocity);
}

bool Unreal::Character::Launch(SDK::ACharacter* characterReference, const SDK::FVector& launchVelocity, const bool& overrideHorizontalVelocity, const bool& overrideVerticalVelocity)
{
	if (characterReference == nullptr || characterReference->CharacterMovement == nullptr
									  || characterReference->CharacterMovement->bCheatFlying
									  || characterReference->CharacterMovement->MovementMode == SDK::EMovementMode::MOVE_None
									  || characterReference->CharacterMovement->IsActive() == false)
		return false;

	characterReference->LaunchCharacter(launchVelocity, overrideHorizontalVelocity, overrideVerticalVelocity);
}
bool Unreal::Character::Launch(const int32_t& playerIndex, const SDK::FVector& launchVelocity, const bool& overrideHorizontalVelocity, const bool& overrideVerticalVelocity)
{
	return Launch(Character::Get(playerIndex), launchVelocity, overrideHorizontalVelocity, overrideVerticalVelocity);
}


bool Unreal::Character::Walk(SDK::ACharacter* characterReference)
{
	if (characterReference == nullptr || characterReference->CharacterMovement == nullptr)
		return false;

	characterReference->SetActorEnableCollision(true);

	characterReference->CharacterMovement->bCheatFlying = false;
	characterReference->CharacterMovement->SetMovementMode(SDK::EMovementMode::MOVE_Walking, 0);

	return true;
}
bool Unreal::Character::Walk(const int32_t& playerIndex)
{
	return Walk(Character::Get(playerIndex));
}

bool Unreal::Character::Fly(SDK::ACharacter* characterReference)
{
	if (characterReference == nullptr || characterReference->CharacterMovement == nullptr)
		return false;

	characterReference->SetActorEnableCollision(true);

	characterReference->CharacterMovement->bCheatFlying = true;
	characterReference->CharacterMovement->SetMovementMode(SDK::EMovementMode::MOVE_Flying, 0);

	return true;
}
bool Unreal::Character::Fly(const int32_t& playerIndex)
{
	return Fly(Character::Get(playerIndex));
}

bool Unreal::Character::Ghost(SDK::ACharacter* characterReference)
{
	if (characterReference == nullptr || characterReference->CharacterMovement == nullptr)
		return false;

	characterReference->SetActorEnableCollision(false);

	characterReference->CharacterMovement->bCheatFlying = true;
	characterReference->CharacterMovement->SetMovementMode(SDK::EMovementMode::MOVE_Flying, 0);

	return true;
}
bool Unreal::Character::Ghost(const int32_t& playerIndex)
{
	return Ghost(Character::Get(playerIndex));
}






std::vector<SDK::UActorComponent*> Unreal::ActorComponent::GetAllOfClass(SDK::AActor* actorReference, const SDK::TSubclassOf<SDK::UActorComponent>& componentClass)
{
	std::vector<SDK::UActorComponent*> outCollection;

	if (actorReference == nullptr)
		return outCollection;

	SDK::TArray<SDK::UActorComponent*> foundComponents = actorReference->K2_GetComponentsByClass(SDK::UActorComponent::StaticClass());
	for (SDK::UActorComponent* actorComponent : foundComponents)
	{
		if (actorComponent == nullptr)
			continue;

		if (actorComponent->IsA(componentClass))
			outCollection.push_back(actorComponent);
	}

	return outCollection;
}


std::vector<SDK::UActorComponent*> Unreal::ActorComponent::GetAll(SDK::AActor* actorReference)
{
	return GetAllOfClass(actorReference, SDK::UActorComponent::StaticClass());
}



SDK::EComponentMobility Unreal::ActorComponent::GetMobility(SDK::USceneComponent* sceneComponentReference)
{
	if (sceneComponentReference == nullptr)
		return SDK::EComponentMobility::Static;

	return sceneComponentReference->Mobility;
}

bool Unreal::ActorComponent::SetMobility(SDK::USceneComponent* sceneComponentReference, SDK::EComponentMobility newMobility)
{
	if (sceneComponentReference == nullptr)
		return false;

	sceneComponentReference->Mobility = newMobility;
	return true;
}

bool Unreal::ActorComponent::MakeStatic(SDK::USceneComponent* sceneComponentReference)
{
	return SetMobility(sceneComponentReference, SDK::EComponentMobility::Static);
}

bool Unreal::ActorComponent::MakeStationary(SDK::USceneComponent* sceneComponentReference)
{
	return SetMobility(sceneComponentReference, SDK::EComponentMobility::Stationary);
}

bool Unreal::ActorComponent::MakeMovable(SDK::USceneComponent* sceneComponentReference)
{
	return SetMobility(sceneComponentReference, SDK::EComponentMobility::Movable);
}


Unreal::Transform Unreal::ActorComponent::GetTransform(SDK::USceneComponent* sceneComponentReference)
{
	if (sceneComponentReference == nullptr)
		return Unreal::Transform();

	return Math::F_ToUnrealTransform(sceneComponentReference->K2_GetComponentToWorld());
}


std::vector<Unreal::ActorComponent::DataStructure> Unreal::ActorComponent::FilterByClassName(const std::vector<ActorComponent::DataStructure>& componentsCollection, const std::string& filter, const bool& caseSensitive)
{
	std::vector<ActorComponent::DataStructure> outCollection;
	size_t filterLength = filter.length();

	/* Filter Components by "Search Filter" */
	for (ActorComponent::DataStructure component : componentsCollection)
	{
		/* "Search Filter" is empty - Component considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
				matchFilters = component.className.find(filter) != std::string::npos;
			else
			{
				std::string filterLowerCase = Utilities::String::ToLowerCase(filter);
				matchFilters = Utilities::String::ToLowerCase(component.className).find(filterLowerCase) != std::string::npos;
			}
		}

		if (matchFilters)
			outCollection.push_back(component); // Component is good to go, can be considered "filtered".
	}

	return outCollection;
}

std::vector<Unreal::ActorComponent::DataStructure> Unreal::ActorComponent::FilterByObjectName(const std::vector<ActorComponent::DataStructure>& componentsCollection, const std::string& filter, const bool& caseSensitive)
{
	std::vector<ActorComponent::DataStructure> outCollection;
	size_t filterLength = filter.length();

	/* Filter Components by "Search Filter" */
	for (ActorComponent::DataStructure component : componentsCollection)
	{
		/* "Search Filter" is empty - Component considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
				matchFilters = component.objectName.find(filter) != std::string::npos;
			else
			{
				std::string filterLowerCase = Utilities::String::ToLowerCase(filter);
				matchFilters = Utilities::String::ToLowerCase(component.objectName).find(filterLowerCase) != std::string::npos;
			}
		}

		if (matchFilters)
			outCollection.push_back(component); // Component is good to go, can be considered "filtered".
	}

	return outCollection;
}

std::vector<Unreal::ActorComponent::DataStructure> Unreal::ActorComponent::FilterByClassAndObjectName(const std::vector<ActorComponent::DataStructure>& componentsCollection, const std::string& filter, const bool& caseSensitive)
{
	std::vector<ActorComponent::DataStructure> outCollection;
	size_t filterLength = filter.length();

	/* Filter Components by "Search Filter" */
	for (ActorComponent::DataStructure component : componentsCollection)
	{
		/* "Search Filter" is empty - Component considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
			{
				bool inClass = component.className.find(filter) != std::string::npos;
				bool inObject = component.objectName.find(filter) != std::string::npos;

				matchFilters = inClass || inObject;
			}
			else
			{
				std::string filterLowerCase = Utilities::String::ToLowerCase(filter);
				bool inClass = Utilities::String::ToLowerCase(component.className).find(filterLowerCase) != std::string::npos;
				bool inObject = Utilities::String::ToLowerCase(component.objectName).find(filterLowerCase) != std::string::npos;

				matchFilters = inClass || inObject;
			}
		}

		if (matchFilters)
			outCollection.push_back(component); // Component is good to go, can be considered "filtered".
	}

	return outCollection;
}






#ifdef ACTOR_KIND
Unreal::Actor::E_ActorKind Unreal::Actor::GetActorKind(SDK::AActor* actorReference)
{
	if (actorReference == nullptr)
		return E_ActorKind::General;

	if (actorReference->IsA(SDK::APointLight::StaticClass()))
		return E_ActorKind::PointLight;

	if (actorReference->IsA(SDK::ASpotLight::StaticClass()))
		return E_ActorKind::SpotLight;

	if (actorReference->IsA(SDK::APawn::StaticClass()))
		return E_ActorKind::Pawn;

	if (actorReference->IsA(SDK::ATextRenderActor::StaticClass()))
		return E_ActorKind::TextRender;

	return E_ActorKind::General;
}
#endif


SDK::EComponentMobility Unreal::Actor::GetMobility(SDK::AActor* actorReference)
{
	if (actorReference == nullptr || actorReference->RootComponent == nullptr)
		return SDK::EComponentMobility::Static;

	return ActorComponent::GetMobility(actorReference->RootComponent);
}

bool Unreal::Actor::SetMobility(SDK::AActor* actorReference, SDK::EComponentMobility newMobility)
{
	if (actorReference == nullptr || actorReference->RootComponent == nullptr)
		return false;

	return ActorComponent::SetMobility(actorReference->RootComponent, newMobility);
}

bool Unreal::Actor::MakeStatic(SDK::AActor* actorReference)
{
	return SetMobility(actorReference, SDK::EComponentMobility::Static);
}

bool Unreal::Actor::MakeStationary(SDK::AActor* actorReference)
{
	return SetMobility(actorReference, SDK::EComponentMobility::Stationary);
}

bool Unreal::Actor::MakeMovable(SDK::AActor* actorReference)
{
	return SetMobility(actorReference, SDK::EComponentMobility::Movable);
}


std::vector<SDK::AActor*> Unreal::Actor::GetAllDefaultOfClass(const SDK::TSubclassOf<SDK::AActor>& actorClass)
{
	std::vector<SDK::AActor*> outCollection;

	int32_t objectsNum = SDK::UObject::GObjects->Num();
	for (int i = 0; i < objectsNum; i++)
	{
		SDK::UObject* objectReference = SDK::UObject::GObjects->GetByIndex(i);

		if (objectReference == nullptr || objectReference->IsDefaultObject() == false)
			continue;

		if (objectReference->IsA(actorClass))
			outCollection.push_back(static_cast<SDK::AActor*>(objectReference)); // Clarify that found Object is of class Actor.
	}

	return outCollection;
}
std::vector<SDK::AActor*> Unreal::Actor::GetAllOfClass(const SDK::TSubclassOf<SDK::AActor>& actorClass)
{
	std::vector<SDK::AActor*> outCollection;

	int32_t objectsNum = SDK::UObject::GObjects->Num();
	for (int i = 0; i < objectsNum; i++)
	{
		SDK::UObject* objectReference = SDK::UObject::GObjects->GetByIndex(i);

		if (objectReference == nullptr || objectReference->IsDefaultObject())
			continue;

		if (objectReference->IsA(actorClass))
			outCollection.push_back(static_cast<SDK::AActor*>(objectReference)); // Clarify that found Object is of class Actor.
	}

	return outCollection;
}


std::vector<SDK::AActor*> Unreal::Actor::GetAllDefault()
{
	return GetAllDefaultOfClass(SDK::AActor::StaticClass());
}
std::vector<SDK::AActor*> Unreal::Actor::GetAll()
{
	return GetAllOfClass(SDK::AActor::StaticClass());
}


std::vector<Unreal::Actor::DataStructure> Unreal::Actor::FilterByClassName(const std::vector<Actor::DataStructure>& actorsCollection, const std::string& filter, const bool& caseSensitive, const float& inDistance)
{
	std::vector<Actor::DataStructure> outCollection;
	size_t filterLength = filter.length();

	SDK::FVector playerLocation = {};
	bool filterByDistance = inDistance > 0.0f;
	if (filterByDistance)
		playerLocation = Unreal::PlayerController::GetLocation(0);

	/* Filter Actors by "Search Filter" */
	for (Unreal::Actor::DataStructure actor : actorsCollection)
	{
		if (filterByDistance)
		{
			if (Math::Vector_Distance(actor.transform.location, playerLocation) > inDistance)
				continue;
		}

		/* "Search Filter" is empty - Actor considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
			{
				bool inClass = actor.className.find(filter) != std::string::npos;
				bool inSuperClass = std::any_of(actor.superClassesNames.begin(), actor.superClassesNames.end(), [&](const std::string& className)
				{
						return className.find(filter) != std::string::npos;
				});

				matchFilters = inClass || inSuperClass;
			}
				
			else
			{
				std::string filterLowerCase = Utilities::String::ToLowerCase(filter);
				bool inClass = Utilities::String::ToLowerCase(actor.className).find(filterLowerCase) != std::string::npos;
				bool inSuperClass = std::any_of(actor.superClassesNames.begin(), actor.superClassesNames.end(), [&](const std::string& className)
				{
					return Utilities::String::ToLowerCase(className).find(filterLowerCase) != std::string::npos;
				});

				matchFilters = inClass || inSuperClass;
			}
		}

		if (matchFilters)
			outCollection.push_back(actor); // Actor is good to go, can be considered "filtered".
	}

	return outCollection;
}

std::vector<Unreal::Actor::DataStructure> Unreal::Actor::FilterByObjectName(const std::vector<Actor::DataStructure>& actorsCollection, const std::string& filter, const bool& caseSensitive, const float& inDistance)
{
	std::vector<Actor::DataStructure> outCollection;
	size_t filterLength = filter.length();

	SDK::FVector playerLocation = {};
	bool filterByDistance = inDistance > 0.0f;
	if (filterByDistance)
		playerLocation = Unreal::PlayerController::GetLocation(0);

	/* Filter Actors by "Search Filter" */
	for (Unreal::Actor::DataStructure actor : actorsCollection)
	{
		if (filterByDistance)
		{
			if (Math::Vector_Distance(actor.transform.location, playerLocation) > inDistance)
				continue;
		}

		/* "Search Filter" is empty - Actor considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
				matchFilters = actor.objectName.find(filter) != std::string::npos;
			else
			{
				std::string filterLowerCase = Utilities::String::ToLowerCase(filter);
				matchFilters = Utilities::String::ToLowerCase(actor.objectName).find(filterLowerCase) != std::string::npos;
			}
		}

		if (matchFilters)
			outCollection.push_back(actor); // Actor is good to go, can be considered "filtered".
	}

	return outCollection;
}

std::vector<Unreal::Actor::DataStructure> Unreal::Actor::FilterByClassAndObjectName(const std::vector<Actor::DataStructure>& actorsCollection, const std::string& filter, const bool& caseSensitive, const float& inDistance)
{
	std::vector<Actor::DataStructure> outCollection;
	size_t filterLength = filter.length();

	SDK::FVector playerLocation = {};
	bool filterByDistance = inDistance > 0.0f;
	if (filterByDistance)
		playerLocation = Unreal::PlayerController::GetLocation(0);

	/* Filter Actors by "Search Filter" */
	for (Unreal::Actor::DataStructure actor : actorsCollection)
	{
		if (filterByDistance)
		{
			if (Math::Vector_Distance(actor.transform.location, playerLocation) > inDistance)
				continue;
		}

		/* "Search Filter" is empty - Actor considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
			{
				bool inClass = actor.className.find(filter) != std::string::npos;
				bool inSuperClass = std::any_of(actor.superClassesNames.begin(), actor.superClassesNames.end(), [&](const std::string& className)
				{
					return className.find(filter) != std::string::npos;
				});
				bool inObject = actor.objectName.find(filter) != std::string::npos;

				matchFilters = inClass || inSuperClass || inObject;
			}
			else
			{
				std::string filterLowerCase = Utilities::String::ToLowerCase(filter);
				bool inClass = Utilities::String::ToLowerCase(actor.className).find(filterLowerCase) != std::string::npos;
				bool inSuperClass = std::any_of(actor.superClassesNames.begin(), actor.superClassesNames.end(), [&](const std::string& className)
					{
						return Utilities::String::ToLowerCase(className).find(filterLowerCase) != std::string::npos;
					});
				bool inObject = Utilities::String::ToLowerCase(actor.objectName).find(filterLowerCase) != std::string::npos;

				matchFilters = inClass || inSuperClass || inObject;
			}
		}

		if (matchFilters)
			outCollection.push_back(actor); // Actor is good to go, can be considered "filtered".
	}

	return outCollection;
}


bool Unreal::Actor::SetActorLocationAndRotation(SDK::AActor* actorReference, const SDK::FVector& location, const SDK::FRotator& rotation, const bool& sweep)
{
	if (actorReference == nullptr)
		return false;

	SDK::EComponentMobility actorMobility = Actor::GetMobility(actorReference);
	bool isUnableToMove = actorMobility != SDK::EComponentMobility::Movable;
	if (isUnableToMove)
		Actor::MakeMovable(actorReference);

	bool isRough = sweep == false;

	SDK::FHitResult hitResult;
	bool isLocationSuccess = actorReference->K2_SetActorLocation(location, sweep, &hitResult, isRough);
	bool isRotationSuccess = actorReference->K2_SetActorRotation(rotation, isRough);

	if (isUnableToMove)
		Actor::SetMobility(actorReference, actorMobility);

	return isLocationSuccess && isRotationSuccess;
}


bool Unreal::Actor::TeleportTo(SDK::AActor* actorReference, const SDK::FVector& location, const SDK::FRotator& rotation)
{
	return SetActorLocationAndRotation(actorReference, location, rotation, false);
}

bool Unreal::Actor::TeleportTo(SDK::AActor* actorReference, const SDK::FVector& location)
{
	if (actorReference == nullptr)
		return false;

	SDK::FRotator rotation = Unreal::Actor::GetRotation(actorReference);
	return TeleportTo(actorReference, location, rotation);
}

bool Unreal::Actor::TeleportTo(SDK::AActor* actorReference, const SDK::FRotator& rotation)
{
	if (actorReference == nullptr)
		return false;

	SDK::FVector location = Unreal::Actor::GetLocation(actorReference);
	return TeleportTo(actorReference, location, rotation);
}


bool Unreal::Actor::SweepTo(SDK::AActor* actorReference, const SDK::FVector& location, const SDK::FRotator& rotation)
{
	return SetActorLocationAndRotation(actorReference, location, rotation, true);
}

bool Unreal::Actor::SweepTo(SDK::AActor* actorReference, const SDK::FVector& location)
{
	if (actorReference == nullptr)
		return false;

	SDK::FRotator rotation = Unreal::Actor::GetRotation(actorReference);
	return SweepTo(actorReference, location, rotation);
}

bool Unreal::Actor::SweepTo(SDK::AActor* actorReference, const SDK::FRotator& rotation)
{
	if (actorReference == nullptr)
		return false;

	SDK::FVector location = Unreal::Actor::GetLocation(actorReference);
	return SweepTo(actorReference, location, rotation);
}


bool Unreal::Actor::GetIsCollisionEnabled(SDK::AActor* actorReference)
{
	if (actorReference == nullptr)
		return false;

	return actorReference->bActorEnableCollision;
}

bool Unreal::Actor::SetIsCollisionEnabled(SDK::AActor* actorReference, const bool& newIsCollisionEnabled)
{
	if (actorReference == nullptr)
		return false;

	actorReference->SetActorEnableCollision(newIsCollisionEnabled);
	return true;
}


bool Unreal::Actor::GetIsVisible(SDK::AActor* actorReference)
{
	if (actorReference == nullptr)
		return false;

	return actorReference->bHidden == false;
}

bool Unreal::Actor::SetIsVisible(SDK::AActor* actorReference, const bool& newIsVisible)
{
	if (actorReference == nullptr)
		return false;
	
	actorReference->SetActorHiddenInGame(newIsVisible == false);
	return true;
}


float Unreal::Actor::GetCustomTimeDilation(SDK::AActor* actorReference)
{
	if (actorReference == nullptr)
		return 0.0f;

	return actorReference->CustomTimeDilation;
}

bool Unreal::Actor::SetCustomTimeDilation(SDK::AActor* actorReference, const float& newCustomTimeDilation)
{
	if (actorReference == nullptr)
		return false;

	actorReference->CustomTimeDilation = newCustomTimeDilation;
	return true;
}


bool Unreal::Actor::SetMaterial(SDK::AActor* actorReference, SDK::UMaterialInterface* materialInterfaceReference)
{
	if (actorReference == nullptr)
		return false;

	if (materialInterfaceReference == nullptr)
		return false;

	std::vector<SDK::UActorComponent*> foundComponents = Unreal::ActorComponent::GetAllOfClass(actorReference, SDK::UPrimitiveComponent::StaticClass());
	for (SDK::UActorComponent* component : foundComponents)
	{
		SDK::UPrimitiveComponent* primitiveComponent = static_cast<SDK::UPrimitiveComponent*>(component);
		for (int8_t i = 0; i < 8; i++)
		{
			primitiveComponent->CreateDynamicMaterialInstance(i, materialInterfaceReference, SDK::FName());
		}
	}

	return true;
}

#ifdef SOFT_PATH
bool Unreal::Actor::SetMaterial(SDK::AActor* actorReference, const std::wstring& materialInterfacePath)
{
	if (actorReference == nullptr)
		return false;

	SDK::UObject* objectReference = Object::SoftLoadObject(materialInterfacePath);
	bool success = false;

	if (objectReference && objectReference->IsA(SDK::UMaterialInstance::StaticClass()))
	{
		SDK::UMaterialInterface* materialInterface = static_cast<SDK::UMaterialInterface*>(objectReference);
		success = SetMaterial(actorReference, materialInterface);
	}

#ifdef SOFT_LOAD_FREEMEMORY
	World::RemoveLevelStreamingByName(Utilities::String::ToString(Unreal::Object::ShortenObjectPath(materialInterfacePath)));
#endif

	return success;
}
#endif


SDK::AActor* Unreal::Actor::Summon(const SDK::TSubclassOf<SDK::AActor>& actorClass, const Unreal::Transform& transform)
{
	SDK::UWorld* world = World::Get();
	if (world == nullptr)
		return nullptr;

	static SDK::FTransform spawnTransform;
	spawnTransform.Translation = transform.location;
	spawnTransform.Rotation = transform.Quat();
	spawnTransform.Scale3D = transform.scale;
#ifdef UE5
	SDK::AActor* actorReference = SDK::UGameplayStatics::BeginDeferredActorSpawnFromClass(world, actorClass, spawnTransform, SDK::ESpawnActorCollisionHandlingMethod::AlwaysSpawn, nullptr, SDK::ESpawnActorScaleMethod::SelectDefaultAtRuntime);
#else
	SDK::AActor* actorReference = SDK::UGameplayStatics::BeginDeferredActorSpawnFromClass(world, actorClass, spawnTransform, SDK::ESpawnActorCollisionHandlingMethod::AlwaysSpawn, nullptr);
#endif
	if (actorReference == nullptr)
		return nullptr;

#ifdef UE5
	SDK::UGameplayStatics::FinishSpawningActor(actorReference, spawnTransform, SDK::ESpawnActorScaleMethod::SelectDefaultAtRuntime);
#else
	SDK::UGameplayStatics::FinishSpawningActor(actorReference, spawnTransform);
#endif

	return actorReference;
}

SDK::AActor* Unreal::Actor::Summon(const SDK::TSubclassOf<SDK::AActor>& actorClass)
{
	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return Unreal::Actor::Summon(actorClass, Unreal::Transform());

	Unreal::Transform transform = Unreal::PlayerController::GetTransform(playerController);
	return Unreal::Actor::Summon(actorClass, transform);
}

#ifdef SOFT_PATH
SDK::AActor* Unreal::Actor::SoftSummon(const std::wstring& actorPath, const Unreal::Transform& transform)
{
	SDK::UClass* actorClass = Object::SoftLoadClass(actorPath);
	SDK::AActor* actor = nullptr;

	if (actorClass)
		actor = Unreal::Actor::Summon(actorClass, transform);

#ifdef SOFT_LOAD_FREEMEMORY
	World::RemoveLevelStreamingByName(Utilities::String::ToString(Unreal::Object::ShortenObjectPath(actorPath)));
#endif

	return actor;
}
#endif


SDK::FVector Unreal::Actor::GetLocation(SDK::AActor* actorReference)
{
	if (actorReference == nullptr)
		return SDK::FVector();

	return actorReference->K2_GetActorLocation();
}

SDK::FRotator Unreal::Actor::GetRotation(SDK::AActor* actorReference)
{
	if (actorReference == nullptr)
		return SDK::FRotator();

	return actorReference->K2_GetActorRotation();
}

SDK::FVector Unreal::Actor::GetScale3D(SDK::AActor* actorReference)
{
	if (actorReference == nullptr)
		return SDK::FVector();

	return actorReference->GetActorScale3D();
}

Unreal::Transform Unreal::Actor::GetTransform(SDK::AActor* actorReference)
{
	if (actorReference == nullptr)
		return Unreal::Transform();

	return Math::F_ToUnrealTransform(actorReference->GetTransform());
}


bool Unreal::Actor::IsValid(SDK::AActor* actorReference)
{
	if (actorReference == nullptr)
		return false;

	SDK::UWorld* world = World::Get();
	if (world)
	{
		/*
			Most of the Actors can be found within arrays of currently loaded game levels.

			Walking through these small arrays, we can save up on performance and only
			use full scan as our last resort - if neither of methods have found the Actor.
		*/

		/* Check is Actor is present within current Persistent Level. */
		if (world->PersistentLevel)
		{
			SDK::TArray<SDK::AActor*>& persistentLevelActors = world->PersistentLevel->Actors;
			for (SDK::AActor* actor : persistentLevelActors)
			{
				if (actor == actorReference)
					return SDK::UKismetSystemLibrary::IsValid(actor);
			}
		}

		/* Walk through all of the streaming levels. */
		if (world->StreamingLevels.Num() > 0)
		{
			for (SDK::ULevelStreaming* levelStreaming : world->StreamingLevels)
			{
				if (levelStreaming->LoadedLevel)
				{
					SDK::TArray<SDK::AActor*>& streamingLevelActors = levelStreaming->LoadedLevel->Actors;
					for (SDK::AActor* actor : streamingLevelActors)
					{
						if (actor == actorReference)
							return SDK::UKismetSystemLibrary::IsValid(actor);
					}
				}
			}
		}
	}

	/* Full scan. Extremely expensive to perform. */
	int32_t objectsNum = SDK::UObject::GObjects->Num();
	for (int i = 0; i < objectsNum; i++)
	{
		SDK::UObject* objectReference = SDK::UObject::GObjects->GetByIndex(i);

		if (objectReference == actorReference)
			return SDK::UKismetSystemLibrary::IsValid(objectReference);
	}
}


bool Unreal::Actor::Destroy(SDK::AActor* actorReference)
{
	if (Unreal::Actor::IsValid(actorReference) == false)
		return false;

	actorReference->K2_DestroyActor();
	return true;
}






SDK::AStaticMeshActor* Unreal::StaticMeshActor::Summon(SDK::UStaticMesh* staticMeshReference, const Unreal::Transform& transform)
{
	if (staticMeshReference == nullptr)
		return nullptr;

	SDK::UWorld* world = World::Get();
	if (world == nullptr)
		return nullptr;

	static SDK::FTransform spawnTransform;
	spawnTransform.Translation = transform.location;
	spawnTransform.Rotation = transform.Quat();
	spawnTransform.Scale3D = transform.scale;
#ifdef UE5
	SDK::AActor* actorReference = SDK::UGameplayStatics::BeginDeferredActorSpawnFromClass(world, SDK::AStaticMeshActor::StaticClass(), spawnTransform, SDK::ESpawnActorCollisionHandlingMethod::AlwaysSpawn, nullptr, SDK::ESpawnActorScaleMethod::SelectDefaultAtRuntime);
#else
	SDK::AActor* actorReference = SDK::UGameplayStatics::BeginDeferredActorSpawnFromClass(world, SDK::AStaticMeshActor::StaticClass(), spawnTransform, SDK::ESpawnActorCollisionHandlingMethod::AlwaysSpawn, nullptr);
#endif
	if (actorReference == nullptr)
		return nullptr;

	SDK::AStaticMeshActor* staticMeshActorReference = static_cast<SDK::AStaticMeshActor*>(actorReference);
	if (staticMeshActorReference->StaticMeshComponent == nullptr)
		return nullptr;

	Unreal::Actor::SetMobility(staticMeshActorReference, SDK::EComponentMobility::Movable);
	staticMeshActorReference->StaticMeshComponent->SetStaticMesh(staticMeshReference);

#ifdef UE5
	SDK::UGameplayStatics::FinishSpawningActor(staticMeshActorReference, spawnTransform, SDK::ESpawnActorScaleMethod::SelectDefaultAtRuntime);
#else
	SDK::UGameplayStatics::FinishSpawningActor(staticMeshActorReference, spawnTransform);
#endif

	return staticMeshActorReference;
}

#ifdef SOFT_PATH
SDK::AStaticMeshActor* Unreal::StaticMeshActor::SoftSummon(const std::wstring& staticMeshPath, const Unreal::Transform& transform)
{
	SDK::UObject* objectReference = Object::SoftLoadObject(staticMeshPath);
	SDK::AStaticMeshActor* staticMeshActor = nullptr;

	if (objectReference && objectReference->IsA(SDK::UStaticMesh::StaticClass()))
	{
		SDK::UStaticMesh* staticMesh = static_cast<SDK::UStaticMesh*>(objectReference);
		staticMeshActor = Unreal::StaticMeshActor::Summon(staticMesh, transform);
	}

#ifdef SOFT_LOAD_FREEMEMORY
	World::RemoveLevelStreamingByName(Utilities::String::ToString(Unreal::Object::ShortenObjectPath(staticMeshPath)));
#endif

	return staticMeshActor;
}
#endif






SDK::ASkeletalMeshActor* Unreal::SkeletalMeshActor::Summon(SDK::USkeletalMesh* skeletalMeshReference, const Unreal::Transform& transform)
{
	if (skeletalMeshReference == nullptr)
		return nullptr;

	SDK::UWorld* world = World::Get();
	if (world == nullptr)
		return nullptr;

	static SDK::FTransform spawnTransform;
	spawnTransform.Translation = transform.location;
	spawnTransform.Rotation = transform.Quat();
	spawnTransform.Scale3D = transform.scale;
#ifdef UE5
	SDK::AActor* actorReference = SDK::UGameplayStatics::BeginDeferredActorSpawnFromClass(world, SDK::ASkeletalMeshActor::StaticClass(), spawnTransform, SDK::ESpawnActorCollisionHandlingMethod::AlwaysSpawn, nullptr, SDK::ESpawnActorScaleMethod::SelectDefaultAtRuntime);
#else
	SDK::AActor* actorReference = SDK::UGameplayStatics::BeginDeferredActorSpawnFromClass(world, SDK::ASkeletalMeshActor::StaticClass(), spawnTransform, SDK::ESpawnActorCollisionHandlingMethod::AlwaysSpawn, nullptr);
#endif
	if (actorReference == nullptr)
		return nullptr;

	SDK::ASkeletalMeshActor* skeletalMeshActorReference = static_cast<SDK::ASkeletalMeshActor*>(actorReference);
	if (skeletalMeshActorReference->SkeletalMeshComponent == nullptr)
		return nullptr;

	Unreal::Actor::SetMobility(skeletalMeshActorReference, SDK::EComponentMobility::Movable);
#ifdef UE5
	skeletalMeshActorReference->SkeletalMeshComponent->SetSkeletalMeshAsset(skeletalMeshReference);
#else
	skeletalMeshActorReference->SkeletalMeshComponent->SetSkeletalMesh(skeletalMeshReference, true);
#endif

#ifdef UE5
	SDK::UGameplayStatics::FinishSpawningActor(skeletalMeshActorReference, spawnTransform, SDK::ESpawnActorScaleMethod::SelectDefaultAtRuntime);
#else
	SDK::UGameplayStatics::FinishSpawningActor(skeletalMeshActorReference, spawnTransform);
#endif

	return skeletalMeshActorReference;
}

#ifdef SOFT_PATH
SDK::ASkeletalMeshActor* Unreal::SkeletalMeshActor::SoftSummon(const std::wstring& skeletalMeshPath, const Unreal::Transform& transform)
{
	SDK::UObject* objectReference = Object::SoftLoadObject(skeletalMeshPath);
	SDK::ASkeletalMeshActor* skeletalMeshActor = nullptr;

	if (objectReference && objectReference->IsA(SDK::USkeletalMesh::StaticClass()))
	{
		SDK::USkeletalMesh* skeletalMesh = static_cast<SDK::USkeletalMesh*>(objectReference);
		skeletalMeshActor = Unreal::SkeletalMeshActor::Summon(skeletalMesh, transform);
	}

#ifdef SOFT_LOAD_FREEMEMORY
	World::RemoveLevelStreamingByName(Utilities::String::ToString(Unreal::Object::ShortenObjectPath(skeletalMeshPath)));
#endif

	return skeletalMeshActor;
}
#endif






std::vector<SDK::UUserWidget*> Unreal::UserWidget::GetAllOfClass(const SDK::TSubclassOf<SDK::UUserWidget>& widgetClass)
{
	std::vector<SDK::UUserWidget*> outCollection;

	int32_t objectsNum = SDK::UObject::GObjects->Num();
	for (int i = 0; i < objectsNum; i++)
	{
		SDK::UObject* objectReference = SDK::UObject::GObjects->GetByIndex(i);

		if (objectReference == nullptr || objectReference->IsDefaultObject())
			continue;

		if (objectReference->IsA(widgetClass))
			outCollection.push_back(static_cast<SDK::UUserWidget*>(objectReference)); // Clarify that found Object is of class User Widget.
	}

	return outCollection;
}


std::vector<SDK::UUserWidget*> Unreal::UserWidget::GetAll()
{
	return GetAllOfClass(SDK::UUserWidget::StaticClass());
}


std::vector<Unreal::UserWidget::DataStructure> Unreal::UserWidget::FilterByClassName(const std::vector<UserWidget::DataStructure>& widgetsCollection, const std::string& filter, const bool& caseSensitive, const bool& topLevelOnly)
{
	std::vector<UserWidget::DataStructure> outCollection;
	size_t filterLength = filter.length();

	/* Filter Widgets by "Search Filter" */
	for (Unreal::UserWidget::DataStructure widget : widgetsCollection)
	{
		if (topLevelOnly && widget.isInViewport == false)
			continue;

		/* "Search Filter" is empty - Widget considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
				matchFilters = widget.className.find(filter) != std::string::npos;
			else
			{
				std::string filterLowerCase = Utilities::String::ToLowerCase(filter);
				matchFilters = Utilities::String::ToLowerCase(widget.className).find(filterLowerCase) != std::string::npos;
			}
		}

		if (matchFilters)
			outCollection.push_back(widget); // Widget is good to go, can be considered "filtered".
	}

	return outCollection;
}

std::vector<Unreal::UserWidget::DataStructure> Unreal::UserWidget::FilterByObjectName(const std::vector<UserWidget::DataStructure>& widgetsCollection, const std::string& filter, const bool& caseSensitive, const bool& topLevelOnly)
{
	std::vector<UserWidget::DataStructure> outCollection;
	size_t filterLength = filter.length();

	/* Filter Widgets by "Search Filter" */
	for (Unreal::UserWidget::DataStructure widget : widgetsCollection)
	{
		if (topLevelOnly && widget.isInViewport == false)
			continue;

		/* "Search Filter" is empty - Widget considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
				matchFilters = widget.objectName.find(filter) != std::string::npos;
			else
			{
				std::string filterLowerCase = Utilities::String::ToLowerCase(filter);
				matchFilters = Utilities::String::ToLowerCase(widget.objectName).find(filterLowerCase) != std::string::npos;
			}
		}

		if (matchFilters)
			outCollection.push_back(widget); // Widget is good to go, can be considered "filtered".
	}

	return outCollection;
}

std::vector<Unreal::UserWidget::DataStructure> Unreal::UserWidget::FilterByClassAndObjectName(const std::vector<UserWidget::DataStructure>& widgetsCollection, const std::string& filter, const bool& caseSensitive, const bool& topLevelOnly)
{
	std::vector<UserWidget::DataStructure> outCollection;
	size_t filterLength = filter.length();

	/* Filter Widgets by "Search Filter" */
	for (Unreal::UserWidget::DataStructure widget : widgetsCollection)
	{
		if (topLevelOnly && widget.isInViewport == false)
			continue;

		/* "Search Filter" is empty - Widget considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
			{
				bool inClass = widget.className.find(filter) != std::string::npos;
				bool inObject = widget.objectName.find(filter) != std::string::npos;

				matchFilters = inClass || inObject;
			}
			else
			{
				std::string filterLowerCase = Utilities::String::ToLowerCase(filter);
				bool inClass = Utilities::String::ToLowerCase(widget.className).find(filterLowerCase) != std::string::npos;
				bool inObject = Utilities::String::ToLowerCase(widget.objectName).find(filterLowerCase) != std::string::npos;

				matchFilters = inClass || inObject;
			}
		}

		if (matchFilters)
			outCollection.push_back(widget); // Widget is good to go, can be considered "filtered".
	}

	return outCollection;
}


SDK::UUserWidget* Unreal::UserWidget::Construct(const SDK::TSubclassOf<SDK::UUserWidget>& widgetClass)
{
	SDK::UWorld* world = World::Get();
	if (world == nullptr)
		return nullptr;

	return SDK::UWidgetBlueprintLibrary::Create(world, widgetClass, nullptr);
}


#ifdef SOFT_PATH
SDK::UUserWidget* Unreal::UserWidget::SoftConstruct(const std::wstring& widgetPath)
{
	SDK::UClass* widgetClass = Object::SoftLoadClass(widgetPath);
	SDK::UUserWidget* widget = nullptr;

	if (widgetClass)
	{
		widget = Unreal::UserWidget::Construct(widgetClass);
	}

#ifdef SOFT_LOAD_FREEMEMORY
	World::RemoveLevelStreamingByName(Utilities::String::ToString(Unreal::Object::ShortenObjectPath(widgetPath)));
#endif

	return widget;
}
#endif






std::vector<SDK::UObject*> Unreal::Object::GetAllDefaultOfClass(const SDK::TSubclassOf<SDK::UObject>& objectClass, const std::vector<SDK::TSubclassOf<SDK::UObject>>& excludeClasses)
{
	std::vector<SDK::UObject*> outCollection;

	int32_t objectsNum = SDK::UObject::GObjects->Num();
	for (int i = 0; i < objectsNum; i++)
	{
		SDK::UObject* objectReference = SDK::UObject::GObjects->GetByIndex(i);

		if (objectReference == nullptr || objectReference->IsDefaultObject() == false)
			continue;

		if (excludeClasses.size() > 0)
		{
			bool shouldBeExcluded = false;
			for (SDK::TSubclassOf<SDK::UObject> subClass : excludeClasses)
			{
				if (objectReference->IsA(subClass))
				{
					shouldBeExcluded = true;
					break;
				}
			}

			if (shouldBeExcluded)
				continue;
		}

		if (objectReference->IsA(objectClass))
			outCollection.push_back(objectReference);
	}

	return outCollection;
}
std::vector<SDK::UObject*> Unreal::Object::GetAllDefaultOfClass(const SDK::TSubclassOf<SDK::UObject>& objectClass)
{
	static const std::vector<SDK::TSubclassOf<SDK::UObject>> excludeClasses = {};
	return GetAllDefaultOfClass(objectClass, excludeClasses);
}
std::vector<SDK::UObject*> Unreal::Object::GetAllOfClass(const SDK::TSubclassOf<SDK::UObject>& objectClass, const std::vector<SDK::TSubclassOf<SDK::UObject>>& excludeClasses)
{
	std::vector<SDK::UObject*> outCollection;

	int32_t objectsNum = SDK::UObject::GObjects->Num();
	for (int i = 0; i < objectsNum; i++)
	{
		SDK::UObject* objectReference = SDK::UObject::GObjects->GetByIndex(i);

		if (objectReference == nullptr || objectReference->IsDefaultObject())
			continue;

		if (excludeClasses.size() > 0)
		{
			bool shouldBeExcluded = false;
			for (SDK::TSubclassOf<SDK::UObject> subClass : excludeClasses)
			{
				if (objectReference->IsA(subClass))
				{
					shouldBeExcluded = true;
					break;
				}
			}

			if (shouldBeExcluded)
				continue;
		}

		if (objectReference->IsA(objectClass))
			outCollection.push_back(objectReference);
	}

	return outCollection;
}
std::vector<SDK::UObject*> Unreal::Object::GetAllOfClass(const SDK::TSubclassOf<SDK::UObject>& objectClass)
{
	static const std::vector<SDK::TSubclassOf<SDK::UObject>> excludeClasses = {};
	return GetAllOfClass(objectClass, excludeClasses);
}


std::vector<SDK::UObject*> Unreal::Object::GetAllDefault(const std::vector<SDK::TSubclassOf<SDK::UObject>>& excludeClasses)
{
	std::vector<SDK::UObject*> outCollection;

	int32_t objectsNum = SDK::UObject::GObjects->Num();
	for (int i = 0; i < objectsNum; i++)
	{
		SDK::UObject* objectReference = SDK::UObject::GObjects->GetByIndex(i);

		if (objectReference == nullptr || objectReference->IsDefaultObject() == false)
			continue;

		if (excludeClasses.size() > 0)
		{
			bool shouldBeExcluded = false;
			for (SDK::TSubclassOf<SDK::UObject> subClass : excludeClasses)
			{
				if (objectReference->IsA(subClass))
				{
					shouldBeExcluded = true;
					break;
				}
			}

			if (shouldBeExcluded)
				continue;
		}

		outCollection.push_back(objectReference);
	}

	return outCollection;
}
std::vector<SDK::UObject*> Unreal::Object::GetAllDefault()
{
	static const std::vector<SDK::TSubclassOf<SDK::UObject>> excludeClasses = {};
	return GetAllDefault(excludeClasses);
}
std::vector<SDK::UObject*> Unreal::Object::GetAll(const std::vector<SDK::TSubclassOf<SDK::UObject>>& excludeClasses)
{
	std::vector<SDK::UObject*> outCollection;

	int32_t objectsNum = SDK::UObject::GObjects->Num();
	for (int i = 0; i < objectsNum; i++)
	{
		SDK::UObject* objectReference = SDK::UObject::GObjects->GetByIndex(i);

		if (objectReference == nullptr || objectReference->IsDefaultObject())
			continue;

		if (excludeClasses.size() > 0)
		{
			bool shouldBeExcluded = false;
			for (SDK::TSubclassOf<SDK::UObject> subClass : excludeClasses)
			{
				if (objectReference->IsA(subClass))
				{
					shouldBeExcluded = true;
					break;
				}
			}

			if (shouldBeExcluded)
				continue;
		}

		outCollection.push_back(objectReference);
	}

	return outCollection;
}
std::vector<SDK::UObject*> Unreal::Object::GetAll()
{
	static const std::vector<SDK::TSubclassOf<SDK::UObject>> excludeClasses = {};
	return GetAll(excludeClasses);
}


std::vector<Unreal::Object::DataStructure> Unreal::Object::FilterByClassName(const std::vector<Object::DataStructure>& objectsCollection, const std::string& filter, const bool& caseSensitive)
{
	std::vector<Object::DataStructure> outCollection;
	size_t filterLength = filter.length();

	/* Filter Objects by "Search Filter" */
	for (Unreal::Object::DataStructure object : objectsCollection)
	{
		/* "Search Filter" is empty - Object considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
			{
				bool inClass = object.className.find(filter) != std::string::npos;
				bool inSuperClass = std::any_of(object.superClassesNames.begin(), object.superClassesNames.end(), [&](const std::string& className)
					{
						return className.find(filter) != std::string::npos;
					});

				matchFilters = inClass || inSuperClass;
			}

			else
			{
				std::string filterLowerCase = Utilities::String::ToLowerCase(filter);
				bool inClass = Utilities::String::ToLowerCase(object.className).find(filterLowerCase) != std::string::npos;
				bool inSuperClass = std::any_of(object.superClassesNames.begin(), object.superClassesNames.end(), [&](const std::string& className)
					{
						return Utilities::String::ToLowerCase(className).find(filterLowerCase) != std::string::npos;
					});

				matchFilters = inClass || inSuperClass;
			}
		}

		if (matchFilters)
			outCollection.push_back(object); // Object is good to go, can be considered "filtered".
	}

	return outCollection;
}

std::vector<Unreal::Object::DataStructure> Unreal::Object::FilterByObjectName(const std::vector<Object::DataStructure>& objectsCollection, const std::string& filter, const bool& caseSensitive)
{
	std::vector<Object::DataStructure> outCollection;
	size_t filterLength = filter.length();

	/* Filter Objects by "Search Filter" */
	for (Object::DataStructure object : objectsCollection)
	{
		/* "Search Filter" is empty - Object considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
				matchFilters = object.objectName.find(filter) != std::string::npos;
			else
			{
				std::string filterLowerCase = Utilities::String::ToLowerCase(filter);
				matchFilters = Utilities::String::ToLowerCase(object.objectName).find(filterLowerCase) != std::string::npos;
			}
		}

		if (matchFilters)
			outCollection.push_back(object); // Object is good to go, can be considered "filtered".
	}

	return outCollection;
}

std::vector<Unreal::Object::DataStructure> Unreal::Object::FilterByClassAndObjectName(const std::vector<Object::DataStructure>& objectsCollection, const std::string& filter, const bool& caseSensitive)
{
	std::vector<Object::DataStructure> outCollection;
	size_t filterLength = filter.length();

	/* Filter Objects by "Search Filter" */
	for (Unreal::Object::DataStructure object : objectsCollection)
	{
		/* "Search Filter" is empty - Object considered a match automatically. */
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
			{
				bool inClass = object.className.find(filter) != std::string::npos;
				bool inSuperClass = std::any_of(object.superClassesNames.begin(), object.superClassesNames.end(), [&](const std::string& className)
					{
						return className.find(filter) != std::string::npos;
					});
				bool inObject = object.objectName.find(filter) != std::string::npos;

				matchFilters = inClass || inSuperClass || inObject;
			}
			else
			{
				std::string filterLowerCase = Utilities::String::ToLowerCase(filter);
				bool inClass = Utilities::String::ToLowerCase(object.className).find(filterLowerCase) != std::string::npos;
				bool inSuperClass = std::any_of(object.superClassesNames.begin(), object.superClassesNames.end(), [&](const std::string& className)
					{
						return Utilities::String::ToLowerCase(className).find(filterLowerCase) != std::string::npos;
					});
				bool inObject = Utilities::String::ToLowerCase(object.objectName).find(filterLowerCase) != std::string::npos;

				matchFilters = inClass || inSuperClass || inObject;
			}
		}

		if (matchFilters)
			outCollection.push_back(object); // Object is good to go, can be considered "filtered".
	}

	return outCollection;
}


#ifdef SOFT_PATH
SDK::UClass* Unreal::Object::SoftLoadClass(const std::wstring& objectPath)
{
	SDK::UWorld* world = World::Get();
	if (world == nullptr)
		return nullptr;

	SDK::FSoftClassPath softClassPath = SDK::UKismetSystemLibrary::MakeSoftClassPath(SDK::FString(objectPath.c_str()));
	SDK::TSoftClassPtr<SDK::UClass> softClassPtr = SDK::UKismetSystemLibrary::Conv_SoftClassPathToSoftClassRef(softClassPath);
	SDK::UClass* objectClass = SDK::UKismetSystemLibrary::Conv_SoftClassReferenceToClass(softClassPtr);

	if (objectClass)
		return objectClass;
	else
	{
		Unreal::LevelStreaming::LoadLevelInstance(objectPath);

		/*
			LoadLevelInstance() take some time to load asset in to a memory;
			Since we can't know when asset will be loaded, we use hardcoded Sleep() assuming it will be enough.
		*/
		int8_t maximumIntervals = 10; // Sleep(10) * 10 = 100ms.
		for (int8_t waitInterval = 0; (objectClass == nullptr && waitInterval < maximumIntervals); ++waitInterval)
		{
			Sleep(10);
			objectClass = SDK::UKismetSystemLibrary::Conv_SoftClassReferenceToClass(softClassPtr);
		}

		if (objectClass)
			return objectClass;
	}

	return nullptr;
}

SDK::UObject* Unreal::Object::SoftLoadObject(const std::wstring& objectPath)
{
	SDK::UWorld* world = World::Get();
	if (world == nullptr)
		return nullptr;

	SDK::FSoftObjectPath softObjectPath = SDK::UKismetSystemLibrary::MakeSoftObjectPath(SDK::FString(objectPath.c_str()));
	SDK::TSoftObjectPtr<SDK::UObject> softObjectPtr = SDK::UKismetSystemLibrary::Conv_SoftObjPathToSoftObjRef(softObjectPath);
	SDK::UObject* objectReference = SDK::UKismetSystemLibrary::Conv_SoftObjectReferenceToObject(softObjectPtr);

	if (objectReference)
		return objectReference;
	else
	{
		Unreal::LevelStreaming::LoadLevelInstance(objectPath);

		/*
			LoadLevelInstance() take some time to load asset in to a memory;
			Since we can't know when asset will be loaded, we use hardcoded Sleep() assuming it will be enough.
		*/
		int8_t maximumIntervals = 10; // Sleep(10) * 10 = 100ms.
		for (int8_t waitInterval = 0; (objectReference == nullptr && waitInterval < maximumIntervals); ++waitInterval)
		{
			Sleep(10);
			objectReference = SDK::UKismetSystemLibrary::Conv_SoftObjectReferenceToObject(softObjectPtr);
		}

		if (objectReference)
			return objectReference;
	}

	return nullptr;
}
#endif


std::wstring Unreal::Object::GetObjectNameFromPath(std::wstring objectPath)
{
	if (objectPath.empty())
	{
		return std::wstring();
	}

	size_t lastDotPos = objectPath.find_last_of(L'.');
	if (lastDotPos != std::wstring::npos)
	{
		return objectPath.substr(lastDotPos + 1);
	}

	size_t lastSlashPos = objectPath.find_last_of(L"/\\");
	if (lastSlashPos != std::wstring::npos)
	{
		return objectPath.substr(lastSlashPos + 1);
	}

	return objectPath;
}


std::wstring Unreal::Object::NormalizeObjectPath(std::wstring objectPath)
{
	const std::wstring contentKey = L"/Content/";
	const std::wstring pluginsKey = L"/Plugins/";
	const std::wstring engineContentKey = L"Engine/Content/";
	const std::wstring engineContentMidKey = L"/Engine/Content/";

	if (objectPath.empty())
	{
		return objectPath;
	}

	static const std::vector<std::wstring> unrealFileExtensions = { L".uasset", L".umap", L".uexp", L".ubulk" };
	for (const std::wstring& fileExtension : unrealFileExtensions)
	{
		objectPath = Utilities::String::Replace(objectPath, fileExtension, std::wstring());
	}
	objectPath = Utilities::String::Replace(objectPath, "\\", "/");

	enum E_ObjectPathSuffixType
	{
		None,
		Object,
		Actor

	};
	E_ObjectPathSuffixType objectPathSuffixType = E_ObjectPathSuffixType::None;

	size_t objectPathLength = objectPath.length();
	if (objectPathLength >= 2)
	{
		size_t objectPathNoSuffixLength = objectPathLength - 2;

		std::wstring objectPathEndChars = objectPath.substr(objectPathNoSuffixLength);
		if (objectPathEndChars == L"--")
		{
			objectPathSuffixType = E_ObjectPathSuffixType::Object;
		}
		if (objectPathEndChars == L"..")
		{
			objectPathSuffixType = E_ObjectPathSuffixType::Actor;
		}

		if (objectPathSuffixType != E_ObjectPathSuffixType::None)
			objectPath = objectPath.substr(0, objectPathNoSuffixLength);
	}

	std::wstring normalizedObjectPath = objectPath;
	bool wasObjectPathNormalized = false;

	if (objectPath.find(engineContentKey) == 0)
	{
		normalizedObjectPath = L"/Engine/" + objectPath.substr(engineContentKey.length());
		wasObjectPathNormalized = true;
	}
	else
	{
		size_t contentPos = objectPath.find(contentKey);
		if (contentPos != std::wstring::npos)
		{
			std::wstring relativePath = objectPath.substr(contentPos + contentKey.length());
			std::wstring rootPath = objectPath.substr(0, contentPos);

			size_t pluginsPos = rootPath.find(pluginsKey);
			if (pluginsPos != std::wstring::npos)
			{
				size_t lastSlash = rootPath.find_last_of('/');
				if (lastSlash != std::wstring::npos)
				{
					std::wstring pluginName = rootPath.substr(lastSlash + 1);

					normalizedObjectPath = L"/" + pluginName + L"/" + relativePath;
					wasObjectPathNormalized = true;
				}
			}

			if (wasObjectPathNormalized == false)
			{
				normalizedObjectPath = L"/Game/" + relativePath;
				wasObjectPathNormalized = true;
			}
		}
	}

	if (objectPathSuffixType != E_ObjectPathSuffixType::None)
	{
		std::wstring assetName = GetObjectNameFromPath(normalizedObjectPath);
		if (objectPathSuffixType == E_ObjectPathSuffixType::Object)
		{
			normalizedObjectPath = normalizedObjectPath + L"." + assetName;
		}
		else
		{
			normalizedObjectPath = normalizedObjectPath + L"." + assetName + L"_C";
		}
	}

	return wasObjectPathNormalized ? normalizedObjectPath : objectPath;
}


std::wstring Unreal::Object::ShortenObjectPath(std::wstring objectPath)
{
	if (objectPath.empty())
	{
		return std::wstring();
	}

	size_t lastDotPos = objectPath.find_last_of(L'.');
	size_t lastSlashPos = objectPath.find_last_of(L"/\\");

	if (lastDotPos != std::wstring::npos && lastDotPos > lastSlashPos)
	{
		return objectPath.substr(0, lastDotPos);
	}

	return objectPath;
}




Unreal::Class::Hierarchy Unreal::Class::GetClassHierarchy(SDK::UObject* objectReference)
{
	Unreal::Class::Hierarchy outHierarchy;

	if (objectReference == nullptr)
		return outHierarchy;

	SDK::UClass* actorClass = objectReference->Class;
	if (actorClass == nullptr)
		return outHierarchy;

	outHierarchy.derivedClass = actorClass;
	while (actorClass)
	{
		if (SDK::UStruct* superStruct = actorClass->SuperStruct)
		{
			actorClass = static_cast<SDK::UClass*>(superStruct);
			outHierarchy.superClasses.push_back(actorClass);
		}
		else
			break;
	}

	return outHierarchy;
}






std::vector<Unreal::Function::DataStructure> Unreal::Function::GetFunctions(SDK::UObject* objectReference, const SDK::EFunctionFlags& hasFlags)
{
	std::vector<Function::DataStructure> outCollection;

	if (objectReference == nullptr || objectReference->Class == nullptr)
		return outCollection;

	SDK::UStruct* currentClass = objectReference->Class;
	while (currentClass)
	{
		for (SDK::UField* uField = currentClass->Children; uField != nullptr; uField = uField->Next)
		{
			if (uField->IsA(SDK::UFunction::StaticClass()))
			{
				SDK::UFunction* uFunction = static_cast<SDK::UFunction*>(uField);
				if ((hasFlags == SDK::EFunctionFlags::None) || (uFunction->FunctionFlags & static_cast<uint32_t>(hasFlags)) != 0)
				{
					Function::DataStructure function;
					function.reference = uFunction;
					function.flags = uFunction->FunctionFlags;
					function.name = uFunction->GetName();

					outCollection.push_back(function);
				}
			}
		}

		currentClass = currentClass->SuperStruct;
	}

	return outCollection;
}


bool Unreal::Function::CallFunction(SDK::UObject* objectReference, SDK::UFunction* functionReference)
{
	if (objectReference == nullptr || functionReference == nullptr)
		return false;

	objectReference->ProcessEvent(functionReference, nullptr);
}

bool Unreal::Function::CallFunction_ThreadSafe(SDK::UObject* objectReference, SDK::UFunction* functionReference)
{
	__try
	{
		return CallFunction(objectReference, functionReference);
	}
	__except (EXCEPTION())
	{
		return false;
	}
}


std::vector<Unreal::Function::DataStructure> Unreal::Function::FilterByName(const std::vector<Function::DataStructure>& functionsCollection, const std::string& filter, const bool& caseSensitive)
{
	std::vector<Function::DataStructure> outCollection;
	size_t filterLength = filter.length();

	for (Function::DataStructure function : functionsCollection)
	{
		bool matchFilters = filterLength == 0;

		if (matchFilters == false)
		{
			if (caseSensitive)
				matchFilters = function.name.find(filter) != std::string::npos;
			else
			{
				std::string filterLowerCase = Utilities::String::ToLowerCase(filter);
				matchFilters = Utilities::String::ToLowerCase(function.name).find(filterLowerCase) != std::string::npos;
			}
		}

		if (matchFilters)
			outCollection.push_back(function);
	}

	return outCollection;
}