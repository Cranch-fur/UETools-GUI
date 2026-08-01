#pragma once
#include "SDK\Engine_classes.hpp"
#include "SDK\UMG_classes.hpp"
#include "SDK\LevelSequence_classes.hpp"

#include "definitions.h"
#include "Math.h"
#include "Utilities.h"






namespace Unreal
{
	struct Transform
	{
		SDK::FVector location;
		SDK::FRotator rotation;
		SDK::FVector scale;

		SDK::FQuat Quat() const
		{
			return Math::Rotator_ToQuat(rotation);
		}
	};

	struct DataStructureBase
	{
		std::string className;
		std::string objectName;
	};

	struct DataStructureBaseWithClassHierarchy : DataStructureBase
	{
		std::vector<std::string> superClassesNames;
	};






	class Console
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::UConsole* reference;
		};


		/*
		* @brief Retrieves the current instance of the Console, if one is available.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::UConsole* Get();

		/*
		* @brief Constructs a Console and assigns it to the active Game Viewport Client.
		* @param ignorePresence - If set to 'True', a new Console will always be created, even if one already exist.
		* @return 'True' if the Console was successfully created and assigned; 'False' otherwise.
		*/
		static bool Construct(bool ignorePresence = false);


		/*
		* @brief Outputs a message in to the Console. Multiple overloads for convenience, including Unreal Engine data types.
		* @param std::wstring
		* @param std::string
		* @param int32_t
		* @param uint32_t
		* @param FVector
		* @param FRotator
		* @param UObject*
		* @param Empty line
		* @return 'True' if the value was successfully printed; 'False' otherwise.
		*/
		static bool Print(const std::wstring& wString);
		static bool Print(const std::string& string);

		static bool Print(int32_t integer);
		static bool Print(uint32_t unsignedInteger);

		static bool Print(const SDK::FVector& vector);
		static bool Print(const SDK::FRotator& rotator);

		static bool Print(SDK::UObject* objectReference);

		static bool Print();


		/*
		* @brief Outputs a set of empty lines in to the Console.
		* @return 'True' if the Console was successfully cleared; 'False' otherwise.
		*/
		static bool Clear();


		static bool ExecuteConsoleCommand(const std::wstring& command);
	};


	class InputSettings
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::UGameViewportClient* reference;
		};


		/*
		* @brief Retrieves the current instance of the Input Settings, if one is available.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::UInputSettings* Get();


		/*
		* @brief Assigns a set of pre-determined key bindings for toggling the Console (open, expand, or close).
		* @return 'True' if the keys were successfully assigned; otherwise 'False'.
		*/
		static bool AssignConsoleBindings();
	};


	class UserInterfaceSettings
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::UUserInterfaceSettings* reference;
		};


		/*
		* @brief Retrieves the current instance of the Input Settings, if one is available.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::UUserInterfaceSettings* Get();


		static bool GetApplicationScale(float* outScale);
		static bool SetApplicationScale(float scale = 1.0f);
	};


	class GameViewportClient
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::UGameViewportClient* reference;

			Console::DataStructure console;
		};


		/*
		* @brief Retrieves the current instance of the Game Viewport Client, if one is available.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::UGameViewportClient* Get();
	};


	class Engine
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::UEngine* reference;

			GameViewportClient::DataStructure gameViewportClient;

			bool fixedFrameRateEnabled;
			double fixedFrameRate;

			bool smoothFrameRateEnabled;
			SDK::FFloatRange smoothFrameRateRange;

			bool subtitlesEnabled;
			bool subtitlesForcedOff;

			bool pauseOnLossOfFocus;
		};


		/*
		* @brief Retrieves the current instance of the Unreal Engine, if one is available.
		* @return A valid pointer to the existing instance; 
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::UEngine* Get();
	};






	class OnlineSession
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::UOnlineSession* reference;
		};
	};


	class GameInstance
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::UGameInstance* reference;

			OnlineSession::DataStructure onlineSession;
		};


		/*
		* @brief Retrieves the current instance of the Game Instance, if one is available.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::UGameInstance* Get();
	};






	class GameSession
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::AGameSession* reference;

			int32_t maxPlayers;
			int32_t maxSpectators;
			int32_t maxPartySize;
			int8_t maxSplitScreensPerConnection;

			std::string sessionName;
		};
	};


	class GameMode
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::AGameModeBase* reference;

			GameSession::DataStructure gameSession;

			int32_t playersCount;
			int32_t spectatorsCount;

			bool startPlayersAsSpectators;
			std::string defaultPlayerName;

			bool useSeamlessTravel;

			std::string options;
			bool isPausable;
		};


		/*
		* @brief Retrieves the current instance of the Game Mode, if one is available.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::AGameModeBase* Get();
	};






	class GameState
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::AGameStateBase* reference;
		};


		/*
		* @brief Retrieves the current instance of the Game State, if one is available.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::AGameStateBase* Get();
	};


	class NetDriver
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::UNetDriver* reference;
		};
	};


	class DemoNetDriver
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::UNetDriver* reference;
		};
	};






	class WorldSettings
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::AWorldSettings* reference;

			bool highPriorityLoading;
			bool localHighPriorityLoading;

			double unitsToMeters;
		};
	};


	class Level
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::ULevel* reference;

			bool isVisible;

			WorldSettings::DataStructure worldSettings;
		};


		static bool CreateLevelSequence(SDK::ULevelSequence* levelSequenceAsset, float startTime, float playRate, int32_t loopCount);
		static bool CreateLevelSequence_ThreadSafe(SDK::ULevelSequence* levelSequenceAsset, float startTime, float playRate, int32_t loopCount);
#ifdef SOFT_PATH
		static bool CreateLevelSequence(const std::wstring& levelSequencePath, float startTime, float playRate, int32_t loopCount);
		static bool CreateLevelSequence_ThreadSafe(const std::wstring& levelSequencePath, float startTime, float playRate, int32_t loopCount);
#endif
	};


	class LevelStreaming
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::ULevelStreaming* reference;

			std::string levelPath;
			SDK::FLinearColor levelColor;

			Level::DataStructure level;
		};


		static std::vector<SDK::ULevelStreaming*> GetAll(SDK::UWorld* worldReference);
		static std::vector<SDK::ULevelStreaming*> GetAll();


		static std::vector<LevelStreaming::DataStructure> FilterByLevelPath(const std::vector<LevelStreaming::DataStructure>& levelStreamingsCollection, const std::string& filter, bool caseSensitive);


#ifdef SOFT_PATH
		static bool LoadLevelInstance(const std::wstring& objectPath, const SDK::FVector& locationOffset = { 0.0f, 0.0f, 0.0f }, const SDK::FRotator& rotationOffset = { 0.0f, 0.0f, 0.0f }, bool useInstancedName = false);
#endif
	};


	class World
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::UWorld* reference;

			GameState::DataStructure gameState;

			NetDriver::DataStructure netDriver;
			DemoNetDriver::DataStructure demoNetDriver;

			Level::DataStructure persistentLevel;

			std::vector<LevelStreaming::DataStructure> levelStreamings;

			double gameTimeInSeconds;

			bool isServer;
			bool isDedicatedServer;
			bool isSplitScreen;
			bool isStandalone;
		};


		/*
		* @brief Retrieves the current instance of the World, if one is available.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::UWorld* Get();


		static bool RemoveLevelStreamingAtIndex(SDK::UWorld* worldReference, int32_t index);
		static bool RemoveLevelStreamingAtIndex(int32_t index);

		static bool RemoveLevelStreamingByName(SDK::UWorld* worldReference, const std::string& levelStreamingName);
		static bool RemoveLevelStreamingByName(const std::string& levelStreamingName);
	};






	class Player
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::UPlayer* reference;
		};
	};


	class Pawn
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::APawn* reference;

			Transform transform;

			bool isControlled;
			bool isPawnControlled;
			bool isPlayerControlled;
			bool isLocallyControlled;
			bool isBotControlled;
		};


		/*
		* @brief Retrieves the current instance of the Pawn, if one is available.
		* @param playerIndex - index of the local player to query.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::APawn* Get(int32_t playerIndex = 0);


		static bool PlayAnimationMontage(SDK::APawn* pawnReference, SDK::UAnimMontage* animationMontageAsset, float startAt, float playRate, bool stopAllMontages);
#ifdef SOFT_PATH
		static bool PlayAnimationMontage(SDK::APawn* pawnReference, const std::wstring& animationMontagePath, float startAt, float playRate, bool stopAllMontages);
#endif


		static bool PlayAnimation(SDK::APawn* pawnReference, SDK::UAnimationAsset* animationAsset, bool looping);
#ifdef SOFT_PATH
		static bool PlayAnimation(SDK::APawn* pawnReference, const std::wstring& animationPath, bool looping);
#endif
	};


	class CameraManager
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::APlayerCameraManager* reference;

			Transform transform;
		};
	};


	class CheatManager
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::UCheatManager* reference;
		};


		/*
		* @brief Retrieves the current instance of the Cheat Manager, if one is available.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::UCheatManager* Get();

		/*
		* @brief Constructs a Cheat Manager and assigns it to the active Player Controller.
		* @param ignorePresence - If set to 'True', a new Cheat Manager will always be created, even if one already exist.
		* @return 'True' if the Cheat Manager was successfully created and assigned; 'False' otherwise.
		*/
		static bool Construct(bool ignorePresence = false);


		/*
		* @brief Calls Summon() function in provided Cheat Manager.
		* Function exist as a workaround and is not recommended to be used
		* unless Actor::Summon() fails for one reason or another.
		* @param cheatManagerReference - Reference to an valid Cheat Manager instance.
		* @param actorClass - Class of the Actor to be summoned.
		* @return 'True' if Actor was attempted to be spawned; 'False' otherwise.
		*/
		static bool Summon(SDK::UCheatManager* cheatManagerReference, SDK::TSubclassOf<SDK::AActor> actorClass);
		/*
		* @brief Creates new Cheat Manager and calls Summon() function in it.
		* Function exist as a workaround and is not recommended to be used
		* unless Actor::Summon() fails for one reason or another.
		* @param actorClass - Class of the Actor to be summoned.
		* @return 'True' if Actor was attempted to be spawned; 'False' otherwise.
		*/
		static bool Summon(const SDK::TSubclassOf<SDK::AActor>& actorClass);


#ifdef SOFT_PATH
		/*
		* @brief Calls Summon() function in provided Cheat Manager.
		* Function exist as a workaround and is not recommended to be used 
		* unless Actor::Summon() fails for one reason or another.
		* @param cheatManagerReference - Reference to an valid Cheat Manager instance.
		* @param actorPath - Class of the Actor to be summoned.
		* @return 'True' if Actor was attempted to be spawned; 'False' otherwise.
		*/
		static bool SoftSummon(SDK::UCheatManager* cheatManagerReference, const std::wstring& actorPath);
		/*
		* @brief Creates new Cheat Manager and calls Summon() function in it.
		* Function exist as a workaround and is not recommended to be used
		* unless Actor::Summon() fails for one reason or another.
		* @param actorPath - Soft path leading to an Actor, for example: "/Game/Blueprints/BP_SentryGun.BP_SentryGun_C".
		* @return 'True' if Actor was attempted to be spawned; 'False' otherwise.
		*/
		static bool SoftSummon(const std::wstring& actorPath);
#endif
	};


	class PlayerController
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::APlayerController* reference;

			Player::DataStructure player;

			Pawn::DataStructure pawn;

			CameraManager::DataStructure cameraManager;

			CheatManager::DataStructure cheatManager;
		};


		/*
		* @brief Retrieves the current instance of the Player Controller, if one is available.
		* @param playerIndex - index of the local player to query.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::APlayerController* Get(int32_t playerIndex = 0);


		static SDK::FVector GetLocation(SDK::APlayerController* playerControllerReference);
		static SDK::FVector GetLocation(int32_t playerIndex);
		static SDK::FRotator GetRotation(SDK::APlayerController* playerControllerReference);
		static SDK::FRotator GetRotation(int32_t playerIndex);
		static SDK::FVector GetScale3D(SDK::APlayerController* playerControllerReference);
		static SDK::FVector GetScale3D(int32_t playerIndex);
		static Unreal::Transform GetTransform(SDK::APlayerController* playerControllerReference);
		static Unreal::Transform GetTransform(int32_t playerIndex);


		static bool SetViewTarget(SDK::AActor* actorReference, SDK::EViewTargetBlendFunction blendFunction, float blendTime, float blendExponent);
		static bool SetViewTarget(SDK::AActor* actorReference);
	};


	class Character
	{
	public:
		/*
		* @brief Retrieves the current instance of the Character, if one is available.
		* @param playerIndex - index of the local player to query.
		* @return A valid pointer to the existing instance;
		*		  otherwise returns 'nullptr' to indicate that no instance is currently accessible.
		*/
		static SDK::ACharacter* Get(int32_t playerIndex = 0);


		static bool Jump(SDK::ACharacter* characterReference);
		static bool Jump(int32_t playerIndex);


		static bool LocalLaunch(SDK::ACharacter* characterReference, const SDK::FVector& launchVelocity, bool overrideHorizontalVelocity = false, bool overrideVerticalVelocity = false);
		static bool LocalLaunch(int32_t playerIndex, const SDK::FVector& launchVelocity, bool overrideHorizontalVelocity = false, bool overrideVerticalVelocity = false);

		static bool Launch(SDK::ACharacter* characterReference, const SDK::FVector& launchVelocity, bool overrideHorizontalVelocity = false, bool overrideVerticalVelocity = false);
		static bool Launch(int32_t playerIndex, const SDK::FVector& launchVelocity, bool overrideHorizontalVelocity = false, bool overrideVerticalVelocity = false);


		static bool Walk(SDK::ACharacter* characterReference);
		static bool Walk(int32_t playerIndex);

		static bool Fly(SDK::ACharacter* characterReference);
		static bool Fly(int32_t playerIndex);

		static bool Ghost(SDK::ACharacter* characterReference);
		static bool Ghost(int32_t playerIndex);
	};






	class ActorComponent
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::UActorComponent* reference;
		};


		/*
		* @brief Retrieves all Actor Components that are instances of specific Actor and of the specified class.
		* @param actorReference - Pointer to Actor to search for Actor Components within.
		* @param componentClass - Class used as a filter when searching for Components.
		* @return A collection of pointers to Components;
		*		  otherwise returns an empty vector if no Components are found.
		*/
		static std::vector<SDK::UActorComponent*> GetAllOfClass(SDK::AActor* actorReference, const SDK::TSubclassOf<SDK::UActorComponent>& componentClass);


		/*
		* @brief Retrieves all Actor Components that are instances of specific Actor and of the specified class.
		* @param actorReference - Pointer to Actor to search for Actor Components within.
		* @return A collection of pointers to Components; otherwise returns an empty vector if no Components are found.
		*/
		static std::vector<SDK::UActorComponent*> GetAll(SDK::AActor* actorReference);


		static SDK::EComponentMobility GetMobility(SDK::USceneComponent* sceneComponentReference);
		static bool SetMobility(SDK::USceneComponent* sceneComponentReference, SDK::EComponentMobility newMobility);
		static bool MakeStatic(SDK::USceneComponent* sceneComponentReference);
		static bool MakeStationary(SDK::USceneComponent* sceneComponentReference);
		static bool MakeMovable(SDK::USceneComponent* sceneComponentReference);


		static Unreal::Transform GetTransform(SDK::USceneComponent* sceneComponentReference);


		static std::vector<ActorComponent::DataStructure> FilterByClassName(const std::vector<ActorComponent::DataStructure>& componentsCollection, const std::string& filter, bool caseSensitive);
		static std::vector<ActorComponent::DataStructure> FilterByObjectName(const std::vector<ActorComponent::DataStructure>& componentsCollection, const std::string& filter, bool caseSensitive);
		static std::vector<ActorComponent::DataStructure> FilterByClassAndObjectName(const std::vector<ActorComponent::DataStructure>& componentsCollection, const std::string& filter, bool caseSensitive);
	};


	class Actor
	{
	public:
		enum class E_ActorKind
		{
			General,
			PointLight,
			SpotLight,
			RectLight,
			DirectionalLight,
			SkyLight,
			SkyAtmosphere,
#ifndef UE5
			AtmosphericFog,
#endif
			ExponentialHeightFog,
			Camera,
			Pawn,
			Decal,
			TextRender
		};
		static E_ActorKind GetActorKind(SDK::AActor* actorReference);


		struct DataStructure : DataStructureBaseWithClassHierarchy
		{
			SDK::AActor* reference;

			E_ActorKind kind;

			Transform transform;

			std::vector<ActorComponent::DataStructure> components;
		};


		static SDK::EComponentMobility GetMobility(SDK::AActor* actorReference);
		static bool SetMobility(SDK::AActor* actorReference, SDK::EComponentMobility newMobility);
		static bool MakeStatic(SDK::AActor* actorReference);
		static bool MakeStationary(SDK::AActor* actorReference);
		static bool MakeMovable(SDK::AActor* actorReference);


		/*
		* @brief Retrieves all existing Actors that are default instances of the specified class.
		* @param actorClass - Class used as a filter when searching for Actors.
		* @return A collection of pointers to all matching Actors;
		*		  otherwise returns an empty vector if no Actors are found.
		*/
		static std::vector<SDK::AActor*> GetAllDefaultOfClass(const SDK::TSubclassOf<SDK::AActor>& actorClass);
		/*
		* @brief Retrieves all existing Actors that are instances of the specified class.
		* @param actorClass - Class used as a filter when searching for Actors.
		* @return A collection of pointers to all matching Actors;
		*		  otherwise returns an empty vector if no Actors are found.
		*/
		static std::vector<SDK::AActor*> GetAllOfClass(const SDK::TSubclassOf<SDK::AActor>& actorClass);


		/*
		* @brief Retrieves all existing Actors that are default instances.
		* @return A collection of pointers to Actors; otherwise returns an empty vector if no Actors are found.
		*/
		static std::vector<SDK::AActor*> GetAllDefault();
		/*
		* @brief Retrieves all existing Actors.
		* @return A collection of pointers to Actors; otherwise returns an empty vector if no Actors are found.
		*/
		static std::vector<SDK::AActor*> GetAll();


		/*
		* @param inDistance - Maximum distance from Player in Units.
		*/
		static std::vector<Actor::DataStructure> FilterByClassName(const std::vector<Actor::DataStructure>& actorsCollection, const std::string& filter, bool caseSensitive, float inDistance = 0.0f);
		/*
		* @param inDistance - Maximum distance from Player in Units.
		*/
		static std::vector<Actor::DataStructure> FilterByObjectName(const std::vector<Actor::DataStructure>& actorsCollection, const std::string& filter, bool caseSensitive, float inDistance = 0.0f);
		/*
		* @param inDistance - Maximum distance from Player in Units.
		*/
		static std::vector<Actor::DataStructure> FilterByClassAndObjectName(const std::vector<Actor::DataStructure>& actorsCollection, const std::string& filter, bool caseSensitive, float inDistance = 0.0f);


		static bool SetLocationAndRotation(SDK::AActor* actorReference, const SDK::FVector& location, const SDK::FRotator& rotation, bool sweep);

		static bool TeleportTo(SDK::AActor* actorReference, const SDK::FVector& location, const SDK::FRotator& rotation);
		static bool TeleportTo(SDK::AActor* actorReference, const SDK::FVector& location);
		static bool TeleportTo(SDK::AActor* actorReference, const SDK::FRotator& rotation);

		static bool SweepTo(SDK::AActor* actorReference, const SDK::FVector& location, const SDK::FRotator& rotation);
		static bool SweepTo(SDK::AActor* actorReference, const SDK::FVector& location);
		static bool SweepTo(SDK::AActor* actorReference, const SDK::FRotator& rotation);


		static bool SetScale3D(SDK::AActor* actorReference, const SDK::FVector& scale3D);


		static bool GetIsCollisionEnabled(SDK::AActor* actorReference);
		static bool SetIsCollisionEnabled(SDK::AActor* actorReference, bool newIsCollisionEnabled);


		static bool GetIsVisible(SDK::AActor* actorReference);
		static bool SetIsVisible(SDK::AActor* actorReference, bool newIsVisible);


		static float GetCustomTimeDilation(SDK::AActor* actorReference);
		static bool SetCustomTimeDilation(SDK::AActor* actorReference, float newCustomTimeDilation);


		static bool SetMaterial(SDK::AActor* actorReference, SDK::UMaterialInterface* materialInterfaceReference, int32_t materialSlot);
		static bool SetMaterial(SDK::AActor* actorReference, SDK::UMaterialInterface* materialInterfaceReference);
#ifdef SOFT_PATH
		static bool SetMaterial(SDK::AActor* actorReference, const std::wstring& materialInterfacePath, int32_t materialSlot);
		static bool SetMaterial(SDK::AActor* actorReference, const std::wstring& materialInterfacePath);
#endif


		static SDK::AActor* Summon(const SDK::TSubclassOf<SDK::AActor>& actorClass, const Unreal::Transform& transform);
		static SDK::AActor* Summon(const SDK::TSubclassOf<SDK::AActor>& actorClass);

#ifdef SOFT_PATH
		static SDK::AActor* SoftSummon(const std::wstring& actorPath, const Unreal::Transform& transform);
#endif


		static SDK::FVector GetLocation(SDK::AActor* actorReference);
		static SDK::FRotator GetRotation(SDK::AActor* actorReference);
		static SDK::FVector GetScale3D(SDK::AActor* actorReference);
		static Unreal::Transform GetTransform(SDK::AActor* actorReference);


		static SDK::FVector GetRelativeLocation(SDK::AActor* actorReference);
		static SDK::FRotator GetRelativeRotation(SDK::AActor* actorReference);
		static SDK::FVector GetRelativeScale3D(SDK::AActor* actorReference);
		static Unreal::Transform GetRelativeTransform(SDK::AActor* actorReference);

		static bool SetRelativeLocationAndRotation(SDK::AActor* actorReference, const SDK::FVector& relativeLocation, const SDK::FRotator& relativeRotation, bool sweep);

		static bool RelativeTeleportTo(SDK::AActor* actorReference, const SDK::FVector& relativeLocation, const SDK::FRotator& relativeRotation);
		static bool RelativeTeleportTo(SDK::AActor* actorReference, const SDK::FVector& relativeLocation);
		static bool RelativeTeleportTo(SDK::AActor* actorReference, const SDK::FRotator& relativeRotation);

		static bool RelativeSweepTo(SDK::AActor* actorReference, const SDK::FVector& relativeLocation, const SDK::FRotator& relativeRotation);
		static bool RelativeSweepTo(SDK::AActor* actorReference, const SDK::FVector& relativeLocation);
		static bool RelativeSweepTo(SDK::AActor* actorReference, const SDK::FRotator& relativeRotation);

		static bool SetRelativeScale3D(SDK::AActor* actorReference, const SDK::FVector& relativeScale3D);


		static bool AttachTo(SDK::AActor* actorReference, SDK::AActor* attachToActorReference, SDK::EAttachmentRule locationRule, SDK::EAttachmentRule rotationRule, SDK::EAttachmentRule scaleRule);
		static bool AttachTo(SDK::AActor* actorReference, SDK::AActor* attachToActorReference, SDK::EAttachmentRule attachementRule);
		static bool AttachTo(SDK::AActor* actorReference, SDK::AActor* attachToActorReference);


		static bool IsValid(SDK::AActor* actorReference);


		static bool Destroy(SDK::AActor* actorReference);
	};






	class StaticMeshActor
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::AStaticMeshActor* reference;
		};


		static SDK::AStaticMeshActor* Summon(SDK::UStaticMesh* staticMeshReference, const Unreal::Transform& transform);

#ifdef SOFT_PATH
		static SDK::AStaticMeshActor* SoftSummon(const std::wstring& staticMeshPath, const Unreal::Transform& transform);
#endif
	};






	class SkeletalMeshActor
	{
	public:
		struct DataStructure : DataStructureBase
		{
			SDK::ASkeletalMeshActor* reference;
		};


		static SDK::ASkeletalMeshActor* Summon(SDK::USkeletalMesh* skeletalMeshReference, const Unreal::Transform& transform);

#ifdef SOFT_PATH
		static SDK::ASkeletalMeshActor* SoftSummon(const std::wstring& skeletalMeshPath, const Unreal::Transform& transform);
#endif
	};






	class PanelWidget
	{
	public:
		struct DataStructure : DataStructureBaseWithClassHierarchy
		{
			SDK::UPanelWidget* reference;
		};
	};






	class UserWidget
	{
	public:
		struct DataStructure : DataStructureBaseWithClassHierarchy
		{
			SDK::UUserWidget* reference;

			bool isTopLevel;
			Unreal::PanelWidget::DataStructure parent;

			SDK::FGeometry cachedGeometry;
			SDK::FVector2D absolutePosition;
			SDK::FVector2D absoluteSize;
			bool isRendered;
		};


		/*
		* @brief Retrieves all existing User Widgets that are instances of the specified class.
		* @param widgetClass - Class used as a filter when searching for Widgets.
		* @return A collection of pointers to User Widgets;
		*		  otherwise returns an empty vector if no Widgets are found.
		*/
		static std::vector<SDK::UUserWidget*> GetAllOfClass(const SDK::TSubclassOf<SDK::UUserWidget>& widgetClass);


		/*
		* @brief Retrieves all existing User Widgets.
		* @return A collection of pointers to User Widgets; otherwise returns an empty vector if no Widgets are found.
		*/
		static std::vector<SDK::UUserWidget*> GetAll();


		static std::vector<UserWidget::DataStructure> FilterByClassName(const std::vector<UserWidget::DataStructure>& widgetsCollection, const std::string& filter, bool caseSensitive, bool topLevelOnly, bool rendered);
		static std::vector<UserWidget::DataStructure> FilterByObjectName(const std::vector<UserWidget::DataStructure>& widgetsCollection, const std::string& filter, bool caseSensitive, bool topLevelOnly, bool rendered);
		static std::vector<UserWidget::DataStructure> FilterByClassAndObjectName(const std::vector<UserWidget::DataStructure>& widgetsCollection, const std::string& filter, bool caseSensitive, bool topLevelOnly, bool rendered);


		static SDK::UUserWidget* Construct(const SDK::TSubclassOf<SDK::UUserWidget>& widgetClass);


#ifdef SOFT_PATH
		static SDK::UUserWidget* SoftConstruct(const std::wstring& widgetPath);
#endif


		static bool GetVisibility(SDK::UUserWidget* widgetReference, SDK::ESlateVisibility* outVisibility);
		static bool SetVisibility(SDK::UUserWidget* widgetReference, SDK::ESlateVisibility newVisibility);
	};
	





	class Object
	{
	public:
		struct DataStructure : DataStructureBaseWithClassHierarchy
		{
			SDK::UObject* reference;
		};


		/*
		* @brief Retrieves all existing Objects that are default instances of the specified class.
		* @param objectClass - Class used as a filter when searching for Objects.
		* @param excludeClasses - Collection of Classes to exclude from matching.
		* @return A collection of pointers to all matching Objects;
		*		  otherwise returns an empty vector if no Objects are found.
		*/
		static std::vector<SDK::UObject*> GetAllDefaultOfClass(const SDK::TSubclassOf<SDK::UObject>& objectClass, const std::vector<SDK::TSubclassOf<SDK::UObject>>& excludeClasses);
		static std::vector<SDK::UObject*> GetAllDefaultOfClass(const SDK::TSubclassOf<SDK::UObject>& objectClass);
		/*
		* @brief Retrieves all existing Objects that are instances of the specified class.
		* @param objectClass - Class used as a filter when searching for Objects.
		* @param excludeClasses - Collection of Classes to exclude from matching.
		* @return A collection of pointers to all matching Objects;
		*		  otherwise returns an empty vector if no Objects are found.
		*/
		static std::vector<SDK::UObject*> GetAllOfClass(const SDK::TSubclassOf<SDK::UObject>& objectClass, const std::vector<SDK::TSubclassOf<SDK::UObject>>& excludeClasses);
		static std::vector<SDK::UObject*> GetAllOfClass(const SDK::TSubclassOf<SDK::UObject>& objectClass);


		/*
		* @brief Retrieves all existing Objects that are default instances.
		* @param excludeClasses - Collection of Classes to exclude from matching.
		* @return A collection of pointers; otherwise returns an empty vector if no Objects are found.
		*/
		static std::vector<SDK::UObject*> GetAllDefault(const std::vector<SDK::TSubclassOf<SDK::UObject>>& excludeClasses);
		static std::vector<SDK::UObject*> GetAllDefault();
		/*
		* @brief Retrieves all existing Objects.
		* @param excludeClasses - Collection of Classes to exclude from matching.
		* @return A collection of pointers; otherwise returns an empty vector if no Objects are found.
		*/
		static std::vector<SDK::UObject*> GetAll(const std::vector<SDK::TSubclassOf<SDK::UObject>>& excludeClasses);
		static std::vector<SDK::UObject*> GetAll();


		static std::vector<Object::DataStructure> FilterByClassName(const std::vector<Object::DataStructure>& objectsCollection, const std::string& filter, bool caseSensitive);
		static std::vector<Object::DataStructure> FilterByObjectName(const std::vector<Object::DataStructure>& objectsCollection, const std::string& filter, bool caseSensitive);
		static std::vector<Object::DataStructure> FilterByClassAndObjectName(const std::vector<Object::DataStructure>& objectsCollection, const std::string& filter, bool caseSensitive);


#ifdef SOFT_PATH
		/*
		* @brief Loads Object Class in to the game memory.
		*/
		static SDK::UClass* SoftLoadClass(const std::wstring& objectPath);
		static SDK::UObject* SoftLoadObject(const std::wstring& objectPath);
#endif


		static SDK::UObject* Construct(const SDK::TSubclassOf<SDK::UObject>& objectClass, SDK::UObject* outer);


		/*
		* @brief See if Object is present in global UObject array.
		* 
		* Function is "ThreadSafe" out of the box.
		*/
		static bool IsValid(SDK::UObject* objectReference);


		static std::wstring GetObjectNameFromPath(std::wstring objectPath);

		static std::wstring NormalizeObjectPath(std::wstring objectPath);

		static std::wstring ShortenObjectPath(std::wstring objectPath);
	};






	class Class
	{
	public:
		struct Hierarchy
		{
			SDK::UClass* derivedClass;
			std::vector<SDK::UClass*> superClasses;
		};


		static Hierarchy GetClassHierarchy(SDK::UObject* objectReference);
	};






	class Function
	{
	public:
		struct DataStructure
		{
			SDK::UFunction* reference;
			uint32_t flags;
			std::string name;
			

			std::string FlagsAsString() const
			{
				if (flags == 0)
					return "None";

				std::string outString;
				uint32_t foundFlags = 0;

				auto checkAndAppendFlag = [&](const char* flagName, uint32_t flagValue)
				{
					if (flags & flagValue)
					{
						if (outString.empty() == false)
							outString += " | ";

						outString += flagName;
						foundFlags |= flagValue;
					}
				};

				checkAndAppendFlag("Final",					 static_cast<uint32_t>(SDK::EFunctionFlags::Final));
				checkAndAppendFlag("RequiredAPI",			 static_cast<uint32_t>(SDK::EFunctionFlags::RequiredAPI));
				checkAndAppendFlag("BlueprintAuthorityOnly", static_cast<uint32_t>(SDK::EFunctionFlags::BlueprintAuthorityOnly));
				checkAndAppendFlag("BlueprintCosmetic",		 static_cast<uint32_t>(SDK::EFunctionFlags::BlueprintCosmetic));
				checkAndAppendFlag("Net",					 static_cast<uint32_t>(SDK::EFunctionFlags::Net));
				checkAndAppendFlag("NetReliable",			 static_cast<uint32_t>(SDK::EFunctionFlags::NetReliable));
				checkAndAppendFlag("NetRequest",			 static_cast<uint32_t>(SDK::EFunctionFlags::NetRequest));
				checkAndAppendFlag("Exec",					 static_cast<uint32_t>(SDK::EFunctionFlags::Exec));
				checkAndAppendFlag("Native",				 static_cast<uint32_t>(SDK::EFunctionFlags::Native));
				checkAndAppendFlag("Event",					 static_cast<uint32_t>(SDK::EFunctionFlags::Event));
				checkAndAppendFlag("NetResponse",			 static_cast<uint32_t>(SDK::EFunctionFlags::NetResponse));
				checkAndAppendFlag("Static",				 static_cast<uint32_t>(SDK::EFunctionFlags::Static));
				checkAndAppendFlag("NetMulticast",			 static_cast<uint32_t>(SDK::EFunctionFlags::NetMulticast));
				checkAndAppendFlag("UbergraphFunction",		 static_cast<uint32_t>(SDK::EFunctionFlags::UbergraphFunction));
				checkAndAppendFlag("MulticastDelegate",		 static_cast<uint32_t>(SDK::EFunctionFlags::MulticastDelegate));
				checkAndAppendFlag("Public",				 static_cast<uint32_t>(SDK::EFunctionFlags::Public));
				checkAndAppendFlag("Private",				 static_cast<uint32_t>(SDK::EFunctionFlags::Private));
				checkAndAppendFlag("Protected",				 static_cast<uint32_t>(SDK::EFunctionFlags::Protected));
				checkAndAppendFlag("Delegate",				 static_cast<uint32_t>(SDK::EFunctionFlags::Delegate));
				checkAndAppendFlag("NetServer",				 static_cast<uint32_t>(SDK::EFunctionFlags::NetServer));
				checkAndAppendFlag("HasOutParms",			 static_cast<uint32_t>(SDK::EFunctionFlags::HasOutParms));
				checkAndAppendFlag("HasDefaults",			 static_cast<uint32_t>(SDK::EFunctionFlags::HasDefaults));
				checkAndAppendFlag("NetClient",				 static_cast<uint32_t>(SDK::EFunctionFlags::NetClient));
				checkAndAppendFlag("DLLImport",				 static_cast<uint32_t>(SDK::EFunctionFlags::DLLImport));
				checkAndAppendFlag("BlueprintCallable",		 static_cast<uint32_t>(SDK::EFunctionFlags::BlueprintCallable));
				checkAndAppendFlag("BlueprintEvent",		 static_cast<uint32_t>(SDK::EFunctionFlags::BlueprintEvent));
				checkAndAppendFlag("BlueprintPure",			 static_cast<uint32_t>(SDK::EFunctionFlags::BlueprintPure));
				checkAndAppendFlag("EditorOnly",			 static_cast<uint32_t>(SDK::EFunctionFlags::EditorOnly));
				checkAndAppendFlag("Const",					 static_cast<uint32_t>(SDK::EFunctionFlags::Const));
				checkAndAppendFlag("NetValidate",			 static_cast<uint32_t>(SDK::EFunctionFlags::NetValidate));

				uint32_t unknownFlags = flags & ~foundFlags;
				if (unknownFlags != 0)
				{
					if (outString.empty() == false)
					{
						outString += " | ";
					}

					outString += std::format("Unknown(0x{:08X})", unknownFlags);
				}

				return outString;
			}


			std::string MemoryAddressAsString() const
			{
				if (reference == nullptr)
					return "nullptr";

				return std::format("{:p}", static_cast<void*>(reference));
			}
		};


		static std::vector<Function::DataStructure> GetFunctions(SDK::UObject* objectReference, SDK::EFunctionFlags hasFlags = SDK::EFunctionFlags::None);

		static bool CallFunction(SDK::UObject* objectReference, SDK::UFunction* functionReference);
		static bool CallFunction_ThreadSafe(SDK::UObject* objectReference, SDK::UFunction* functionReference);


		static std::vector<Function::DataStructure> FilterByName(const std::vector<Function::DataStructure>& functionsCollection, const std::string& filter, bool caseSensitive);
	};






#ifdef WAIT_FOR_TITLE_INIT
	static bool IsTitleInitialized()
	{
		if (SDK::UObject::GObjects == nullptr || SDK::UObject::GObjects->Num() == 0)
			return false;

		return Unreal::GameInstance::Get();
	}
#endif
};