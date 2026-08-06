#pragma once
#include "imgui.h"

#include "definitions.h"
#if defined(API_D3D11)
	#include "DirectWindow11.h"
#elif defined(API_OPENGL3)
	#include "OpenWindow3.h"
#endif

#include "ConfigInstance.h"
#include "Unreal.h"
#include "Math.h"

#include <thread>






namespace ImGui
{
	struct Viewport
	{
		ImGuiViewport* iViewport;
		ImVec2 iViewportPosition;
		ImVec2 iViewportSize;
	};
	Viewport GetViewport();


	static ImDrawList* drawList;
	ImDrawList* GetDrawList();


	class Texture2D
	{
	private:
		static inline std::unordered_map<std::string, ImTextureID> ImTextures;

	public:
		static bool Exists(const std::string& textureName);
		static bool Exists(const Window::TextureMetaData& textureMetaData);

		static ImTextureID Get(const std::string& textureName);
		static ImTextureID Get(const Window::TextureMetaData& textureMetaData);

		static void Add(const std::string& textureName, ImTextureID iTextureId);
		static void Add(const Window::TextureMetaData& textureMetaData, ImTextureID iTextureId);

		static bool IsValid(const ImTextureID& iTextureId);
	};

	bool IconButton(const char* textureName, const char* text, const ImVec2& size = { 96.0f, 96.0f });
	bool IconButton(const Window::TextureMetaData& textureMetaData, const char* text, const ImVec2& size = { 96.0f, 96.0f });


	class Color
	{
	public:
		static inline ImU32 Red = IM_COL32(204, 77, 51, 255);
		static inline ImU32 Green = IM_COL32(51, 204, 77, 255);
		static inline ImU32 Blue = IM_COL32(51, 102, 204, 255);
		static inline ImU32 White = IM_COL32(255, 255, 255, 255);
		static inline ImU32 Black = IM_COL32(0, 0, 0, 255);
		static inline ImU32 Alpha = IM_COL32(0, 0, 0, 0);
	};

	class LinearColor
	{
	public:
		static inline ImVec4 Red = ImGui::ColorConvertU32ToFloat4(Color::Red);
		static inline ImVec4 Green = ImGui::ColorConvertU32ToFloat4(Color::Green);
		static inline ImVec4 Blue = ImGui::ColorConvertU32ToFloat4(Color::Blue);
		static inline ImVec4 White = ImGui::ColorConvertU32ToFloat4(Color::White);
		static inline ImVec4 Black = ImGui::ColorConvertU32ToFloat4(Color::Black);
		static inline ImVec4 Alpha = ImGui::ColorConvertU32ToFloat4(Color::Alpha);
	};
	

	void TextBool(const char* label, bool inBool, const char* text_true, const char* text_false, bool useColoring, ImU32 color_true, ImU32 color_false);
	void TextBool(const char* label, bool inBool);
	void TextBoolColored(const char* label, bool status);
	void TextBoolPresence(const char* label, bool presence);
	void TextBoolPresenceColored(const char* label, bool presence);
	void TextBoolMultiplePresence(const char* label, bool presence);
	void TextBoolMultiplePresenceColored(const char* label, bool presence);


	void TextFloat(const char* label, float value, bool useColoring, ImU32 color_positive, ImU32 color_negative);
	void TextFloat(const char* label, float value);
	void TextFloatColored(const char* label, float value);


	void TextInt(const char* label, int32_t value, bool useColoring, ImU32 color_positive, ImU32 color_negative);
	void TextInt(const char* label, int32_t value);
	void TextIntColored(const char* label, int32_t value);


	void TextVector(const char* label, const SDK::FVector& value, bool useColoring, ImU32 color_positive, ImU32 color_negative);
	void TextVector(const char* label, const SDK::FVector& value);
	void TextVectorColored(const char* label, const SDK::FVector& value);


	void TextRotator(const char* label, const SDK::FRotator& value, bool useColoring, ImU32 color_positive, ImU32 color_negative);
	void TextRotator(const char* label, const SDK::FRotator& value);
	void TextRotatorColored(const char* label, const SDK::FRotator& value);


	void AddHint(const char* hint);
	void AddHint_OnItemHovered(const char* hint);
	void AddHint_OnItemFocused(const char* hint);
	void AddHint_OnItemActive(const char* hint);
	void AddHint_OnItemEdited(const char* hint);
	void QuestionMarkHint(const char* hint);


	void TextCopyable(const char* fmt, ...);


	void ReadOnlyInputText(const char* label, const char* text, bool showCopyButton = true);


	bool SliderIntEditable(const char* label, int32_t* v, int32_t v_min, int32_t v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
	bool SliderFloatEditable(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
	bool SliderDoubleEditable(const char* label, double* v, double v_min, double v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);


	bool ColorConfig3(const char* label, float color[3]);
	bool ColorConfig4(const char* label, float color[4]);


	template<typename Container, typename Func>
	inline void PaginatedList(const char* id, int32_t* currentPage, Container& rows, int32_t rowsPerPage, Func FnRenderRow)
	{
		if (currentPage == nullptr)
			return;

		int32_t totalRows = rows.size();
		if (totalRows == 0)
			return;

		int32_t totalPages = (totalRows + rowsPerPage - 1) / rowsPerPage;

		if (*currentPage >= totalPages)
		{
			int32_t lastPage = totalPages - 1;
			*currentPage = (lastPage > 0) ? lastPage : 0;
		}

		ImGui::PushID(id);

		if (totalPages > 1)
		{
			int32_t nextFramePage = *currentPage;

			if (ImGui::Button("<<"))
			{
				nextFramePage -= 10;
			}
			ImGui::SameLine();
			if (ImGui::Button("<"))
			{
				nextFramePage -= 1;
			}
			ImGui::SameLine();
			ImGui::SetNextItemWidth(300.0f);
			int32_t displayPage = *currentPage + 1;
			if (ImGui::SliderInt("##PageSlider", &displayPage, 1, totalPages, "Page %d"))
			{
				nextFramePage = displayPage - 1;
			}
			ImGui::SameLine();
			if (ImGui::Button(">"))
			{
				nextFramePage += 1;
			}
			ImGui::SameLine();
			if (ImGui::Button(">>"))
			{
				nextFramePage += 10;
			}

			if (nextFramePage < 0)
			{
				nextFramePage = 0;
			}
			else if (nextFramePage >= totalPages)
			{
				nextFramePage = totalPages - 1;
			}

			*currentPage = nextFramePage;

			ImGui::Separator();
		}

		int32_t startIndex = *currentPage * rowsPerPage;

		int32_t projectedEnd = startIndex + rowsPerPage;
		int32_t endIndex = projectedEnd < totalRows ? projectedEnd : totalRows;

		for (int32_t i = startIndex; i < endIndex; ++i)
		{
			FnRenderRow(rows[i]);
		}

		ImGui::PopID();
	}


	enum E_ObjectFilterMode
	{
		ClassName,
		ObjectName,
		All
	};
	bool ObjectFilterModeComboBox(const char* label, E_ObjectFilterMode* v);


	/*
	* @brief Using pre-determined table, converts an ImGui key to the corresponding WinAPI virtual-key code.
	* @param key - ImGui key to be converted.
	* @return The corresponding WinAPI virtual-key code, or 0 if unsupported.
	*/
	static int ImGuiKey_ToWinAPI(const ImGuiKey& key);
	/*
	* @brief Using pre-determined table, returns a human-readable name for a given ImGui key.
	* @param key - ImGui key to get the name of.
	* @return The key name as a string.
	*/
	static const char* ImGuiKey_GetName(const ImGuiKey& key);


	struct KeyBinding
	{
		ImGuiKey key = ImGuiKey_None;
		bool isDetermined = true;
		bool isInUse = false;
	};
	/*
	* @brief Renders a key binding input control in ImGui.
	* 
	* Displays a button with the current binding state and allows the user
	* to assign or unbind a key interactively.
	* 
	* @param label - label text to display (may contain "##" to hide ID).
	* @param binding - pointer to key binding structure.
	* @return 'True' if the binding was changed; otherwise 'False'
	*/
	bool KeyBindingInput(const char* label, KeyBinding* binding);
	bool IsKeyBindingPressed(KeyBinding* binding, bool waitForRelease = true);
	bool IsKeyBindingDown(KeyBinding* binding);
	bool IsKeyBindingReleased(KeyBinding* binding);
	

	enum E_MouseButton
	{
		Left,
		Middle,
		Right
	};
	bool IsMouseButtonDown(const E_MouseButton& mouseButton);


	enum E_FontScale
	{
		Tiny,
		Little,
		Small,
		Regular,
		Big,
		Large,
		Title,
		Custom
	};
	static inline E_FontScale fontScale = E_FontScale::Regular;

	/*
	* @brief Sets the font scale to the specified value.
	* @param fontScale - scale factor.
	*/
	static void SetFontScale(float fontScale);
	/*
	* @brief Sets the font scale to the specified type.
	* @param fontScale - E_FontScale type.
	*/
	static void SetFontScale(E_FontScale fontScale);

	/*
	* @brief Sets the font scale to 0.5x.
	*/
	static void SetFontTiny();
	/*
	* @brief Sets the font scale to 0.75x.
	*/
	static void SetFontLittle();
	/*
	* @brief Sets the font scale to 0.9x.
	*/
	static void SetFontSmall();
	/*
	* @brief Sets the font scale to 1.0x.
	*/
	static void SetFontRegular();
	/*
	* @brief Sets the font scale to 1.1x.
	*/
	static void SetFontBig();
	/*
	* @brief Sets the font scale to 1.25x.
	*/
	static void SetFontLarge();
	/*
	* @brief Sets the font scale to 1.5x.
	*/
	static void SetFontTitle();


	static void TinyText(const char* fmt, ...);
	static void LittleText(const char* fmt, ...);
	static void SmallText(const char* fmt, ...);
	static void BigText(const char* fmt, ...);
	static void LargeText(const char* fmt, ...);
	static void TitleText(const char* fmt, ...);




	/*
	* @brief New Line + Separator + New Line.
	*/
	static void CategorySeparator()
	{
		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();
	}


	/*
	* @brief Prints pre-determined number of spaces to expand menu horizontally.
	*/
	static void MenuSpacer()
	{
		static const char* menuSpacer = "                                                                                               ";
		ImGui::TextUnformatted(menuSpacer, menuSpacer + 95);
	}
};






class GUI
{
private:
	static inline HANDLE windowThread = nullptr;
public:
	static HANDLE GetWindowThread()
	{
		return windowThread;
	}
	static bool StartWindowThread();


private:
	static inline bool isTitleInFocus = false;
public:
	static bool GetIsTitleInFocus()
	{
		return isTitleInFocus;
	}
	static void SetIsTitleInFocus(bool newIsInFocus)
	{
		isTitleInFocus = newIsInFocus;
	}


private:
	static inline bool isMenuActive = false;
public:
	static bool GetIsMenuActive()
	{
		return isMenuActive;
	}
	static void SetIsMenuActive(bool newIsActive)
	{
		isMenuActive = newIsActive;
	}
	static void ToggleIsMenuActive()
	{
		isMenuActive = !isMenuActive;
	}


#ifdef _DEBUG
private:
	static inline int8_t menuDebugLevel = 0;
public:
	static int8_t GetMenuDebugLevel()
	{
		return menuDebugLevel;
	}
	static bool GetIsMenuDebugEnabled()
	{
		return menuDebugLevel > 0;
	}
	static bool GetIsMenuDebugDetailed()
	{
		return menuDebugLevel == 2;
	}
	static void SetMenuDebugLevel(int8_t newMenuDebugLevel)
	{
		menuDebugLevel = newMenuDebugLevel;
	}
	static void SwitchMenuDebugLevel()
	{
		int8_t newMenuDebugLevel = menuDebugLevel + 1;
		if (newMenuDebugLevel > 2)
			menuDebugLevel = 0;
		else
			menuDebugLevel = newMenuDebugLevel;
	}
#endif




public:
	/*
	* @brief Initializes the GUI system. Should be called to start ImGui and create the menu.
	* @param applicationModule - Handle of the current (this) DLL module.
	*/
	static void Init(const HMODULE& applicationModule);
#ifdef WAIT_FOR_TITLE_INIT
	/*
	* @brief Initializes the GUI system once general Unreal Engine subsystems are up and running. Should be called to start ImGui and create the menu.
	* @param applicationModule - Handle of the current (this) DLL module.
	*/
	static void InitOnTitleInitialized(const HMODULE& applicationModule);
#endif


	/*
	* @brief Renders frame of GUI elements.
	* 
	* Called once per frame by DirectWindow class (on each ImGui::NewFrame())
	* to draw application-specific ImGui controls and windows.
	*/
	static void Draw();




public:
	enum class E_Sound
	{
		BUTTON_PRESS,
		BUTTON_CANCEL,
		ACTION_SUCCESS,
		ACTION_ERROR
	};
	static void PlayUISound(const E_Sound& soundToPlay);
	static void PlayActionSound(bool wasSuccessfull)
	{
		PlayUISound(wasSuccessfull ? E_Sound::ACTION_SUCCESS : E_Sound::ACTION_ERROR);
	}






	class SharedFunctions
	{
	public:
		static void Ghost();
		static void Fly();
		static void Walk();


	public:
		static void Jump();


	public:
		static void Launch();
		static void Dash();
	};
};






namespace Features
{
	class Config
	{
	private:
		template <typename T>
		static void ReadFeatureFromConfig(ConfigInstance* featuresConfig, const std::string& entryName, T* featureValue);

	public:
		static void Load();
		static void Save();
	};




	class Menu
	{
	public:
		static inline bool enableSound = true;

		static inline ImFont* fontBitmap = nullptr;
		static inline ImFont* fontVector = nullptr;
		static inline bool useVectorFont = true;

		static inline float opacity = 1.0f;
	};




	class Debug
	{
	public:
		static inline bool enabled;

		static inline double lastUpdateTime;

		static inline bool autoUpdate = false;
		static inline float autoUpdateDelay = 0.25f;

		static inline Unreal::Engine::DataStructure engine;

		static inline Unreal::GameInstance::DataStructure gameInstance;

		static inline Unreal::GameMode::DataStructure gameMode;

		static inline Unreal::PlayerController::DataStructure playerController;

		static inline Unreal::World::DataStructure world;

		static inline bool wasProjectNameObtained;
		static inline std::string projectName;

		static inline bool wasProjectPlatformObtained;
		static inline std::string projectPlatform;

		static inline bool wasEngineVersionObtained;
		static inline std::string engineVersion;

		static inline bool wasUsernameObtained;
		static inline std::string username;

		static inline bool wasCommandLineObtained;
		static inline std::string commandLine;


		static void Update();
		static void Update_ThreadSafe();
	};




#ifdef SOFT_PATH
	class ActorSummon
	{
	public:
		static inline const size_t pathBufferSize = SIZE_BUFFER_MULTIOBJECTPATH;
		static inline char pathBuffer[pathBufferSize] = {};

		static inline float location[3];
		static inline bool usePlayerLocation = true;
		static inline float rotation[3];
		static inline bool usePlayerRotation = true;
		static inline float scale[3] = { 1.0f, 1.0f, 1.0f };
		static inline bool usePlayerScale = false;
	};
#endif




	class Functions
	{
	public:
		static inline std::vector<Unreal::Function::DataStructure> functions;
		static inline SDK::UObject* functionsOwner;

		static inline const size_t filterBufferSize = SIZE_BUFFER_SEARCHFILTER;
		static inline char filterBuffer[filterBufferSize] = {};
		static inline bool filterCaseSensitive = false;
	};




	class ActorsList
	{
	public:
		static inline const size_t filterBufferSize = SIZE_BUFFER_SEARCHFILTER;
		static inline char filterBuffer[filterBufferSize] = {};
		static inline bool filterCaseSensitive = false;
		static inline ImGui::E_ObjectFilterMode filterMode = ImGui::E_ObjectFilterMode::All;
		static inline float filterDistance = 0.0f;

		static inline std::vector<Unreal::Actor::DataStructure> actors;
		static inline std::vector<Unreal::Actor::DataStructure> filteredActors;

		static inline int32_t currentPage = 0;
		static inline const int32_t rowsPerPage = 25;

		static inline float viewTargetBlendTime = 1.0f;
		static inline float viewTargetBlendExponent = 1.0f;

		static inline Unreal::Actor::DataStructure actorToAttach = {};

		static Unreal::Actor::DataStructure GetActorData(SDK::AActor* actorReference);
		static void Update();
		static void Update(const Unreal::Actor::DataStructure& actor);
		static void Filter();


		static inline const size_t componentsFilterBufferSize = SIZE_BUFFER_SEARCHFILTER;
		static inline char componentsFilterBuffer[componentsFilterBufferSize] = {};
		static inline bool componentsFilterCaseSensitive = false;
		static inline ImGui::E_ObjectFilterMode componentsFilterMode = ImGui::E_ObjectFilterMode::All;
	};




	class WidgetsList
	{
	public:
		static inline const size_t filterBufferSize = SIZE_BUFFER_SEARCHFILTER;
		static inline char filterBuffer[filterBufferSize] = {};
		static inline bool filterCaseSensitive = false;
		static inline ImGui::E_ObjectFilterMode filterMode = ImGui::E_ObjectFilterMode::All;
		static inline bool filterTopLevelOnly = true;
		static inline bool filterRenderedOnly = true;

		static inline std::vector<Unreal::UserWidget::DataStructure> widgets;
		static inline std::vector<Unreal::UserWidget::DataStructure> filteredWidgets;

		static inline int32_t currentPage = 0;
		static inline const int32_t rowsPerPage = 10;


		static Unreal::UserWidget::DataStructure GetWidgetData(SDK::UUserWidget* widgetReference);
		static void Update();
		static void Update(const Unreal::UserWidget::DataStructure& widget);
		static void Filter();
	};




	class WidgetVisualisation
	{
	public:
		static inline Unreal::UserWidget::DataStructure widgetToVisualise = {};

		static inline float color[4] = { 1.0f, 0.0f, 1.0f, 1.0f };
		static inline float lineThickness = 2.0f;


		static void Draw();
		static void Draw_ThreadSafe();
	};




	class ObjectConstruct
	{
	public:
		static inline const size_t pathBufferSize = SIZE_BUFFER_MULTIOBJECTPATH;
		static inline char pathBuffer[pathBufferSize] = {};
	};




	class ObjectsList
	{
	public:
		static inline const size_t filterBufferSize = SIZE_BUFFER_SEARCHFILTER;
		static inline char filterBuffer[filterBufferSize] = {};
		static inline bool filterCaseSensitive = false;
		static inline ImGui::E_ObjectFilterMode filterMode = ImGui::E_ObjectFilterMode::All;

		static inline std::vector<Unreal::Object::DataStructure> objects;
		static inline std::vector<Unreal::Object::DataStructure> filteredObjects;

		static inline int32_t currentPage = 0;
		static inline const int32_t rowsPerPage = 25;


		static Unreal::Object::DataStructure GetObjectData(SDK::UObject* objectReference);
		static void Update();
		static void Update(const Unreal::Object::DataStructure& object);
		static void Filter();
	};




	class ActorTrace
	{
	public:
		static inline bool showOnScreen = true;

		static inline SDK::FVector traceStartLocation;
		static inline SDK::FVector traceEndLocation;
		static inline float traceColor[4] = { 0.118f, 1.0f, 0.0f, 1.0f };
		static inline float traceThickness = 3.5f;
		static inline float traceDistance = 200.0f;

		static inline bool traceCast; // When set to True, indicates that user have casted a ray; would render a dummy { 0.0, 0.0 } - { 0.0, 0.0 } line otherwise.
		static inline bool traceHit;

#ifdef UE5
		static inline Unreal::Object::DataStructure object;
#else
		static inline Unreal::Actor::DataStructure actor;
#endif


		static bool Trace();

		static void Draw();
		static void Draw_ThreadSafe();
	};




	class ActorsTracker
	{
	public:
		static inline bool enabled = false;

		static inline float actorColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

		static inline bool showDistance = true;
		static inline bool fadeOnCloseup = true;


		static void Draw();
		static void Draw_ThreadSafe();
	};




#ifdef COLLISION_VISUALIZER
	class CollisionVisualizer
	{
	public:
		static inline bool enabled = false;

		/* Blueish - Collision/Physics related. */
		static inline float color_StaticMesh[4] = { 0.0f, 0.5f, 1.0f, 1.0f };
		static inline float color_Primitive[4] = { 0.0f, 0.8f, 1.0f, 1.0f };
		static inline float color_PhysicsVolume[4] = { 0.3f, 0.25f, 0.85f, 1.0f };

		/* Reddish - Damage/Restriction related. */
		static inline float color_BlockingVolume[4] = { 1.0f, 0.25f, 0.2f, 1.0f };

		/* Greenish - Event related (e.g: trigger). */
		static inline float color_TriggerVolume[4] = { 0.3f, 1.0f, 0.3f, 1.0f };

		/* Pinkish - Post Processing. */
		static inline float color_PostProcessVolume[4] = { 0.8f, 0.2f, 0.8f, 1.0f };

		/* White - Unknown/Other. */
		static inline float color_Other[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

		static inline float thickness = 1.0f;


		static void Draw();
		static void Draw_ThreadSafe();
	};
#endif




#ifdef SOFT_PATH
	class ActorMaterial
	{
	public:
		static inline const size_t materialInstancePathBufferSize = SIZE_BUFFER_SINGLEOBJECTPATH;
		static inline char materialInstancePathBuffer[materialInstancePathBufferSize] = {};

		static inline int32_t materialSlot;
		static inline bool useAllMaterialSlots = true;
	};
#endif




#ifdef SOFT_PATH
	class PawnAnimation
	{
	public:
		static inline const size_t animationMontagePathBufferSize = SIZE_BUFFER_SINGLEOBJECTPATH;
		static inline char animationMontagePathBuffer[animationMontagePathBufferSize] = {};
		static inline float animationMontageStartAt = 0.0f;
		static inline float animationMontagePlayRate = 1.0f;
		static inline bool animationMontageStopAllMontages = true;

		static inline const size_t animationPathBufferSize = SIZE_BUFFER_SINGLEOBJECTPATH;
		static inline char animationPathBuffer[animationPathBufferSize] = {};
		static inline bool animationLooping = false;
	};
#endif




#ifdef SOFT_PATH
	class WidgetConstruct
	{
	public:
		/* Allocate large buffer to account for combined paths (e.g: "/Game/Blueprints/Watermelon.Watermelon_C | /Game/Blueprints/Cookie.Cookie_C") */
		static inline const size_t pathBufferSize = SIZE_BUFFER_MULTIOBJECTPATH;
		static inline char pathBuffer[pathBufferSize] = {};

		static inline int32_t zOrder = 0;
	};
#endif




	class LevelStreaming
	{
	public:
				static inline const size_t filterBufferSize = SIZE_BUFFER_SEARCHFILTER;
		static inline char filterBuffer[filterBufferSize] = {};
		static inline bool filterCaseSensitive = false;

		static inline std::vector<Unreal::LevelStreaming::DataStructure> levels;
		static inline std::vector<Unreal::LevelStreaming::DataStructure> filteredLevels;

		static inline bool useEditorColors = false;

		static inline int32_t currentPage = 0;
		static inline const int32_t rowsPerPage = 10;


		static Unreal::LevelStreaming::DataStructure GetLevelStreamingData(SDK::ULevelStreaming* levelStreamingReference);
		static void Update();
		static void Update(const Unreal::LevelStreaming::DataStructure& levelStreaming);
		static void Filter();
	};




#ifdef SOFT_PATH
	class LoadLevelInstance
	{
	public:
		/* Allocate large buffer to account for combined paths (e.g: "/Game/OpenWorld/Tile_X2Y8.Tile_X2Y8 | /Game/OpenWorld/Tile_X4Y6.Tile_X4Y6") */
		static inline const size_t levelPathBufferSize = SIZE_BUFFER_MULTIOBJECTPATH;
		static inline char levelPathBuffer[levelPathBufferSize] = {};

		static inline float locationOffset[3];
		static inline float rotationOffset[3];
	};




	class PlayLevelSequence
	{
	public:
		/* Allocate large buffer to account for combined paths (e.g: "/Game/OpenWorld/Sequences/LS_TowerExplosion.LS_TowerExplosion | /Game/OpenWorld/Sequences/LS_CrowdRunning.LS_CrowdRunning") */
		static inline const size_t levelSequencePathBufferSize = SIZE_BUFFER_MULTIOBJECTPATH;
		static inline char levelSequencePathBuffer[levelSequencePathBufferSize] = {};

		static inline float startTime = 0.0f;
		static inline float playRate = 1.0f;
		static inline int32_t loopCount = 0;
	};
#endif




	class CharacterMovement
	{
	public:
		static void Ghost();
		static void Fly();
		static void Walk();


		static void Jump();


		static inline double launchVelocityX = 0.0f;
		static inline double launchVelocityY = 0.0f;
		static inline double launchVelocityZ = 1325.0f;
		static void Launch();


		static inline double dashStrength = 3375.0f;
		static void Dash();
	};




	class Camera
	{
	public:
		static inline float fadeFromAlpha = 0.0f;
		static inline float fadeToAlpha = 1.0f;
		static inline float fadeDuration = 2.5f;
		static inline float fadeColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		static inline bool fadeAudio = false;
		static inline bool fadePersistent = true;


		static void StartFade();
		static void StopFade();
	};




	class DirectionalMovement
	{
	public:
		static inline bool enabled = false;

		static inline bool omniMovement = true;
		static inline bool isUpMovementExpected = false;
		static inline bool isDownMovementExpected = false;

		static inline bool independentOmniMovement = false;
		static inline bool isForwardMovementExpected = false;
		static inline bool isBackwardMovementExpected = false;
		static inline bool isLeftMovementExpected = false;
		static inline bool isRightMovementExpected = false;


		static inline float step = 15.0f;
		static inline float delay = 0.05f;
	};




	class Positions
	{
	private:
		static inline const std::string entryPrefix = "position_";
		static inline const std::string entryTitleSuffix = "_Title";
		static inline const std::string entryLocationSuffix = "_Location";
		static inline const std::string entryRotationSuffix = "_Rotation";

	public:
		static inline const int32_t entriesLimit = 1000;

		static inline const size_t newEntryTitleBufferSize = SIZE_BUFFER_POSITIONSENTRY;
		static inline char newEntryTitleBuffer[newEntryTitleBufferSize] = {};

		struct PositionEntry
		{
			std::string title;
			SDK::FVector location;
			SDK::FRotator rotation;
		};
		static inline std::vector<Positions::PositionEntry> entries;

	private:
		static bool ReadPositionFromConfig(ConfigInstance* positionsConfig, int32_t positionId, Positions::PositionEntry* positionEntry);

	public:
		static void Load();
		static void Save();
	};




	class FreeCamera
	{
	public:
		static inline SDK::ACameraActor* cameraReference;

		static inline SDK::AActor* lastViewTarget;

		static inline bool forceFreezePlayer = true;
		static inline float storedCustomTimeDilation;

		static inline bool forceDisablePlayerInput = false;
		static inline bool wasMoveInputIgnored;
		static inline bool wasLookInputIgnored;

		static inline float cameraMovementStep = 3.0f;
		static inline float cameraRotationStep = 0.25f;

		static inline bool useMouseControl = true;
		static inline bool mouseControlOnHold = false;
		static inline bool mouseControlXInverted = false;
		static inline bool mouseControlYInverted = true;
		static inline float mouseControlSensitivity = 0.1f;
		static inline bool mouseControlLimitMaximumDelta = false;
		static inline float mouseControlMaximumDelta = 25.0f;


		static bool IsEnabled();
		static bool Enable();
		static bool Disable();
		static void Toggle();

		static bool Move(float forwardStep, float rightStep, float upStep);
		static bool Rotate(float horizontalStep, float verticalStep);

		static bool TeleportPlayerToCamera();
		static bool TeleportCameraToPlayer();
	};




	class ConsoleCommands
	{
	public:
		static inline std::vector<Unreal::Function::DataStructure> commands;

		static inline const size_t filterBufferSize = SIZE_BUFFER_SEARCHFILTER;
		static inline char filterBuffer[filterBufferSize] = {};
		static inline bool filterCaseSensitive = false;

		static void Update();
	};




	class BootlegConsole
	{
	public:
		/* Allocate large buffer to account for combined console commands (e.g: "stat fps | stat unit") */
		static inline const size_t bufferSize = SIZE_BUFFER_CONSOLE;
		static inline char buffer[bufferSize] = {};
	};
};






namespace BackgroundTasks
{
	class KeybindingsHandler
	{
	private:
		static inline bool isEnabled = false;

		static inline float delay = 0.001f;

		static inline HANDLE thread = nullptr;
		static void Worker();

	public:
		static void Enable();
		static void Disable();
	};

	class DirectionalMovementHandler
	{
	private:
		static inline bool isEnabled = false;

		static inline float& delay = Features::DirectionalMovement::delay;

		static inline HANDLE thread = nullptr;
		static void Worker();

	public:
		static void Enable();
		static void Disable();
	};

#ifdef TASK_CONSTRUCT_CONSOLE
	class ConstructConsole
	{
	private:
		static inline bool isEnabled = false;

		static inline bool consoleConstructed = false;
		static inline bool consoleBindingsAssigned = false;

		static inline float delay = 1.0f;

		static inline HANDLE thread = nullptr;
		static void Worker();

	public:
		static void Enable();
		static void Disable();
	};
#endif

#ifdef TASK_CONSTRUCT_CHEATMANAGER
	class ConstructCheatManager
	{
	private:
		static inline bool isEnabled = false;

		static inline bool cheatManagerConstructed = false;

		static inline float delay = 1.0f;

		static inline HANDLE thread = nullptr;
		static void Worker();

	public:
		static void Enable();
		static void Disable();
	};
#endif

	static void Init();
}






namespace Inputs
{
	class Config
	{
	private:
		static void ReadKeyBindingFromConfig(ConfigInstance* keybindingsConfig, const std::string& entryName, ImGui::KeyBinding* keyBinding);

	public:
		static void Load();
		static void Save();
	};




	class Keybindings
	{
	public:
		static inline ImGui::KeyBinding general_MenuOpenClose{ ImGuiKey_Insert };


		static inline ImGui::KeyBinding debug_ActorTrace;

		static inline ImGui::KeyBinding debug_ActorsListUpdate;

		static inline ImGui::KeyBinding debug_ActorsListTracking;

#ifdef COLLISION_VISUALIZER
		static inline ImGui::KeyBinding debug_ActorsListCollisionDraw;
#endif

		static inline ImGui::KeyBinding characterMovement_Ghost;
		static inline ImGui::KeyBinding characterMovement_Fly;
		static inline ImGui::KeyBinding characterMovement_Walk;
		static inline ImGui::KeyBinding characterMovement_Jump;
		static inline ImGui::KeyBinding characterMovement_Launch;
		static inline ImGui::KeyBinding characterMovement_Dash;

		static inline ImGui::KeyBinding characterOmniMovement_Up{ ImGuiKey_E };
		static inline ImGui::KeyBinding characterOmniMovement_Down{ ImGuiKey_Q };;
		static inline ImGui::KeyBinding characterOmniMovement_Forward{ ImGuiKey_W };;
		static inline ImGui::KeyBinding characterOmniMovement_Backward{ ImGuiKey_S };;
		static inline ImGui::KeyBinding characterOmniMovement_Left{ ImGuiKey_A };;
		static inline ImGui::KeyBinding characterOmniMovement_Right{ ImGuiKey_D };;

		static inline ImGui::KeyBinding characterCamera_StartFade;
		static inline ImGui::KeyBinding characterCamera_StopFade;

		static inline ImGui::KeyBinding freeCamera_Toggle;
		static inline ImGui::KeyBinding freeCamera_TeleportPlayerToCamera;
		static inline ImGui::KeyBinding freeCamera_TeleportCameraToPlayer;
		static inline ImGui::KeyBinding freeCamera_MoveUp{ ImGuiKey_E };
		static inline ImGui::KeyBinding freeCamera_MoveDown{ ImGuiKey_Q };
		static inline ImGui::KeyBinding freeCamera_MoveForward{ ImGuiKey_W };
		static inline ImGui::KeyBinding freeCamera_MoveBackward{ ImGuiKey_S };
		static inline ImGui::KeyBinding freeCamera_MoveLeft{ ImGuiKey_A };
		static inline ImGui::KeyBinding freeCamera_MoveRight{ ImGuiKey_D };
		static inline ImGui::KeyBinding freeCamera_RotateUp{ ImGuiKey_UpArrow };
		static inline ImGui::KeyBinding freeCamera_RotateDown{ ImGuiKey_DownArrow };
		static inline ImGui::KeyBinding freeCamera_RotateLeft{ ImGuiKey_LeftArrow };
		static inline ImGui::KeyBinding freeCamera_RotateRight{ ImGuiKey_RightArrow };
	};
};






#ifdef COLLISION_VISUALIZER
class DebugDraw
{
private:
	static inline std::unordered_map<SDK::FKConvexElem*, std::vector<int32_t>> convexIndicesCache;

public:
	static void DrawConvexElement(SDK::FKConvexElem* convexElement, const Unreal::Transform& componentTransform, uint32_t drawColor, float drawThickness);

	static void DrawBodySetup(SDK::UBodySetup* bodySetup, const Unreal::Transform& componentTransform, uint32_t drawColor, float drawThickness);
	static void DrawVolume(SDK::AVolume* volume, uint32_t drawColor, float drawThickness);

	static void DrawStaticMeshComponent(SDK::UStaticMeshComponent* staticMeshComponent, uint32_t drawColor, float drawThickness);
	static void DrawInstancedStaticMeshComponent(SDK::UInstancedStaticMeshComponent* instancedStaticMeshComponent, uint32_t drawColor, float drawThickness);

	static void DrawSkeletalMeshComponent(SDK::USkeletalMeshComponent* skeletalMeshComponent, bool drawAllSockets, uint32_t drawColor, float drawThickness);

	static void DrawCapsuleComponent(SDK::UCapsuleComponent* capsuleComponent, uint32_t drawColor, float drawThickness);
	static void DrawSphereComponent(SDK::USphereComponent* sphereComponent, uint32_t drawColor, float drawThickness);
	static void DrawBoxComponent(SDK::UBoxComponent* boxComponent, uint32_t drawColor, float drawThickness);
	static void DrawSplineComponent(SDK::USplineComponent* splineComponent, uint32_t drawColor, float drawThickness);
};
#endif






namespace Templates
{
	class ClassHierarchy
	{
	public:
		static void Draw(const std::vector<std::string>& superClassesNames);
	};

	class Functions
	{
	public:
		static void Draw(SDK::UObject* objectReference);
	};

	class LocationRotationScale
	{
	public:
		static void Draw(SDK::AActor* actorReference);
	};

	namespace Descriptions
	{
		class HDR
		{
		public:
			static void Draw();
		};

#ifdef SOFT_PATH
		class SoftPath
		{
		public:
			static void Draw(const char* typeName, const char* examplePath);
		};
#endif
	}

	namespace Menus
	{
		class Debug
		{
		private:
			static void Sub_Engine();
			static void Sub_GameInstance();
			static void Sub_GameMode();
			static void Sub_PlayerController();
			static void Sub_World();
			static void Sub_Actors();
			static void Sub_Actors_ThreadSafe();
			static void Sub_Actors_Kind(const Unreal::Actor::DataStructure& actor);
			static void Sub_Actors_Components(const Unreal::Actor::DataStructure& actor);
			static void Sub_Widgets();
			static void Sub_Widgets_ThreadSafe();
			static void Sub_Objects();
			static void Sub_Objects_ThreadSafe();

		public:
			static void Draw();
		};

		class World
		{
		public:
			static void Draw();
			static void Draw_ThreadSafe();
		};

		class Character
		{
		public:
			static void Draw();
			static void Draw_ThreadSafe();
		};

		class FreeCamera
		{
		public:
			static void Draw();
		};

		class Settings
		{
		public:
			static void Draw();
		};

		class BootlegConsole
		{
		public:
			static void Draw();
		};
	};
}