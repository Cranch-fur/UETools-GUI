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
#include <atomic>
#include <mutex>






struct ImGuiErrorRecoveryState;

namespace ImGui
{
	/* Restores ImGui stacks (windows, IDs, trees, etc.) after an SEH exception interrupted drawing. */
	void RecoverFromException(const ImGuiErrorRecoveryState* state);


	struct Viewport
	{
		ImGuiViewport* iViewport;
		ImVec2 iViewportPosition;
		ImVec2 iViewportSize;
	};
	Viewport GetViewport();


	ImDrawList* GetDrawList();


	class Texture2D
	{
	private:
		static inline std::unordered_map<std::string, ImTextureID> ImTextures;

		/* Resource compiler stores resource names in upper case, so names are compared case-insensitively. */
		static std::string NormalizeName(const std::string& textureName);

	public:
		/* Texture name is a resource name from PNG section of UETools-GUI.rc (e.g. "Friendly"). */
		static bool Exists(const std::string& textureName);
		static ImTextureID Get(const std::string& textureName);
		static void Add(const std::string& textureName, ImTextureID iTextureId);

		/* Releases every texture through backend specific function and empties the collection. */
		static void Clear(const std::function<void(ImTextureID)>& FnReleaseTexture);

		static bool IsValid(ImTextureID iTextureId);
	};

	bool IconButton(const char* textureName, const char* text, const ImVec2& size = { 96.0f, 96.0f });


	class Color
	{
	public:
		static inline ImU32 Red = IM_COL32(204, 77, 51, 255);
		static inline ImU32 Green = IM_COL32(51, 204, 77, 255);
		static inline ImU32 Blue = IM_COL32(51, 102, 204, 255);
		static inline ImU32 Cyan = IM_COL32(77, 204, 204, 255);
		static inline ImU32 Yellow = IM_COL32(255, 214, 51, 255);
		static inline ImU32 Pink = IM_COL32(255, 140, 199, 255);
		static inline ImU32 Orange = IM_COL32(255, 153, 51, 255);
		static inline ImU32 Grey = IM_COL32(158, 158, 158, 255);
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
		static inline ImVec4 Cyan = ImGui::ColorConvertU32ToFloat4(Color::Cyan);
		static inline ImVec4 Yellow = ImGui::ColorConvertU32ToFloat4(Color::Yellow);
		static inline ImVec4 Pink = ImGui::ColorConvertU32ToFloat4(Color::Pink);
		static inline ImVec4 Orange = ImGui::ColorConvertU32ToFloat4(Color::Orange);
		static inline ImVec4 Grey = ImGui::ColorConvertU32ToFloat4(Color::Grey);
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


	bool InputDouble3(const char* label, double v[3], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);


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

		for (int32_t i = startIndex; i < endIndex && i < rows.size(); ++i)
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
	int32_t ImGuiKey_ToWinAPI(ImGuiKey key);
	/*
	* @brief Using pre-determined table, returns a human-readable name for a given ImGui key.
	* @param key - ImGui key to get the name of.
	* @return The key name as a string.
	*/
	const char* ImGuiKey_GetName(ImGuiKey key);


	struct KeyBinding
	{
		ImGuiKey key = ImGuiKey_None;
		bool isDetermined = true;
		bool isInUse = false;

		bool wasDown = false; // Key state observed on previous poll.
		uint64_t lastPollTick = 0; // GetTickCount64() of previous poll.
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
	bool IsMouseButtonDown(E_MouseButton mouseButton);


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
	inline E_FontScale fontScale = E_FontScale::Regular;

	/*
	* @brief Sets the font scale to the specified value.
	* @param fontScale - scale factor.
	*/
	void SetFontScale(float fontScale);
	/*
	* @brief Sets the font scale to the specified type.
	* @param fontScale - E_FontScale type.
	*/
	void SetFontScale(E_FontScale fontScale);

	/*
	* @brief Sets the font scale to 0.5x.
	*/
	void SetFontTiny();
	/*
	* @brief Sets the font scale to 0.75x.
	*/
	void SetFontLittle();
	/*
	* @brief Sets the font scale to 0.9x.
	*/
	void SetFontSmall();
	/*
	* @brief Sets the font scale to 1.0x.
	*/
	void SetFontRegular();
	/*
	* @brief Sets the font scale to 1.1x.
	*/
	void SetFontBig();
	/*
	* @brief Sets the font scale to 1.25x.
	*/
	void SetFontLarge();
	/*
	* @brief Sets the font scale to 1.5x.
	*/
	void SetFontTitle();


	void TinyText(const char* fmt, ...);
	void LittleText(const char* fmt, ...);
	void SmallText(const char* fmt, ...);
	void BigText(const char* fmt, ...);
	void LargeText(const char* fmt, ...);
	void TitleText(const char* fmt, ...);




	/*
	* @brief New Line + Separator + New Line.
	*/
	inline void CategorySeparator()
	{
		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();
	}


	/*
	* @brief Prints pre-determined number of spaces to expand menu horizontally.
	*/
	inline void MenuSpacer()
	{
		const char* menuSpacer = "                                                                                               ";
		ImGui::TextUnformatted(menuSpacer, menuSpacer + 95);
	}




	enum class E_OverlayCorner
	{
		TopLeft = 0,
		TopRight = 1,
		BottomLeft = 2,
		BottomRight = 3,
		None = -1
	};

	/*
	* @brief Keeps window with given name inside display area; must be called before ImGui::Begin() of that window.
	* @param windowName - Name of the window, exactly as passed to ImGui::Begin().
	*/
	void SetNextWindowInsideDisplay(const char* windowName);

	/*
	* @brief Creates a scalable overlay window.
	* @param name - Display name and unique identifier (e.g. "Title##ID").
	* @param p_open - Pointer to a boolean state to allow closing the overlay.
	* @param isMenuActive - If false, the overlay becomes click-through and unmovable.
	* @param defaultCorner - The corner where the overlay will spawn on its first use.
	* @return 'True' if the window is not collapsed/hidden. ALWAYS call ImGui::End() after this, regardless of the return value.
	*/
	bool BeginOverlay(const char* name, bool* p_open, bool isMenuActive, E_OverlayCorner defaultCorner = E_OverlayCorner::TopRight);
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

	/* Stops background tasks and restores title state; must be called before the module is unloaded. */
	static void Shutdown();


private:
	static inline std::atomic<bool> isUnloadRequested = false;
public:
	static bool GetIsUnloadRequested()
	{
		return isUnloadRequested;
	}
	/* Asks overlay to shut down and unload the module from the title process. */
	static void RequestUnload()
	{
		isUnloadRequested = true;
	}


private:
	static inline std::atomic<bool> isTitleInFocus = false;
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
	static inline std::atomic<bool> isMenuActive = false;
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
	static void Init(HMODULE applicationModule);
#ifdef WAIT_FOR_TITLE_INIT
	/*
	* @brief Initializes the GUI system once general Unreal Engine subsystems are up and running. Should be called to start ImGui and create the menu.
	* @param applicationModule - Handle of the current (this) DLL module.
	*/
	static void InitOnTitleInitialized(HMODULE applicationModule);
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
	static void PlayUISound(E_Sound soundToPlay);
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

		static constexpr float INTERFACE_SCALE_MIN = 0.5f;
		static constexpr float INTERFACE_SCALE_MAX = 2.0f;
		static inline float interfaceScale = 1.0f;

		/* Scales style sizes & fonts by interfaceScale; does nothing if scale hasn't changed since last call. */
		static void ApplyInterfaceScale();
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

		static inline double location[3];
		static inline bool usePlayerLocation = true;
		static inline double rotation[3];
		static inline bool usePlayerRotation = true;
		static inline double scale[3] = { 1.0f, 1.0f, 1.0f };
		static inline bool usePlayerScale = false;
	};
#endif




	class Functions
	{
	public:
		static inline std::vector<Unreal::Function::DataStructure> functions;
		static inline SDK::UObject* functionsOwner;

#ifdef FUNCTION_PARAMETERS
		/* User provided values of parameters, keyed by parameter property. */
		static inline std::unordered_map<void*, Unreal::Function::ParameterValue> parameterValues;

		/* Return value & out parameters received on last call, keyed by parameter property. */
		static inline std::unordered_map<void*, std::string> outputValues;
#endif

		static inline const size_t filterBufferSize = SIZE_BUFFER_SEARCHFILTER;
		static inline char filterBuffer[filterBufferSize] = {};
		static inline bool filterCaseSensitive = false;
	};




#ifdef OBJECT_PROPERTIES
	class Properties
	{
	public:
		static inline std::vector<Unreal::Property::DataStructure> properties;
		static inline SDK::UObject* propertiesOwner;

		/* Edited values of simple-type properties, keyed by property; refreshed from live memory while not edited. */
		static inline std::unordered_map<void*, Unreal::Property::PropertyValue> values;

		static inline const size_t filterBufferSize = SIZE_BUFFER_SEARCHFILTER;
		static inline char filterBuffer[filterBufferSize] = {};
		static inline bool filterCaseSensitive = false;
	};
#endif




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




	class ActorGizmo
	{
	public:
		enum class E_Handle 
		{
			None, 
			MoveX, 
			MoveY, 
			MoveZ, 
			ScaleX, 
			ScaleY, 
			ScaleZ, 
			ScaleUniform 
		};

		static inline SDK::AActor* target = nullptr;

		static inline float size = 110.0f; // Axis length on screen, in pixels.
		static inline float snapLocation = 10.0f; // Location step while Ctrl is held (units).
		static inline float snapScale = 0.1f; // Scale step while Ctrl is held.

		static bool IsEditing(SDK::AActor* actorReference);
		static void SetEditing(SDK::AActor* actorReference, bool enabled);

		static void Draw();
		static void Draw_ThreadSafe();

	private:
		static constexpr float GIZMO_PICK_RADIUS = 9.0f; // Mouse distance (pixels) to grab a handle.
		static constexpr float GIZMO_SCALE_KNOB_POSITION = 0.6f; // Scale knobs sit at this fraction of the axis length.

		static inline E_Handle hoveredHandle = E_Handle::None;
		static inline E_Handle activeHandle = E_Handle::None;

		static inline ImVec2 dragStartMouse;
		static inline ImVec2 dragAxisScreen; // Normalized screen direction of the dragged axis.
		static inline float dragPixelsPerUnit = 1.0f; // Screen pixels per world unit along the dragged move axis.
		static inline float dragHandleLength = 1.0f; // Screen distance from the center to the dragged scale knob.
		static inline SDK::FVector dragStartLocation;
		static inline SDK::FVector dragStartScale;
	};




	class ActorHighlight
	{
	public:
		static inline bool enabled = true;
		static inline float color[4] = { 1.0f, 0.6f, 0.1f, 1.0f };

		/* Called by Actors List while the Actor's row is hovered. */
		static void SetHovered(SDK::AActor* actorReference, const std::string& label);

		static void Draw();
		static void Draw_ThreadSafe();

	private:
		static constexpr float EMPTY_BOUNDS_EXTENT = 25.0f;

		static inline SDK::AActor* hoveredActor = nullptr;
		static inline std::string hoveredLabel;
		static inline int32_t hoveredFrame = -1;
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
		static inline bool fill = false;
		static inline float fillOpacity = 0.25f;


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

		static inline double locationOffset[3];
		static inline double rotationOffset[3];
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




	class ConsoleDictionary
	{
	public:
		enum class E_Requirement
		{
			None = 0,
			CheatManager = 1 << 0,
			Development = 1 << 1 
		};

		friend constexpr E_Requirement operator|(E_Requirement A, E_Requirement B) { return static_cast<E_Requirement>(static_cast<uint8_t>(A) | static_cast<uint8_t>(B)); }
		friend constexpr E_Requirement operator&(E_Requirement A, E_Requirement B) { return static_cast<E_Requirement>(static_cast<uint8_t>(A) & static_cast<uint8_t>(B)); }

		static constexpr bool HasRequirement(E_Requirement requirements, E_Requirement requirement) { return (requirements & requirement) != E_Requirement::None; }

		struct Entry
		{
			std::string command;
			std::string hint; // Free-form argument hint, e.g. "{x} {y} {z}" ("" = none).
			std::string description;
			E_Requirement requirements;

			std::string DisplayText() const;
			bool Requires(E_Requirement requirement) const { return HasRequirement(requirements, requirement); }
		};

		/* Built-in console command dictionary (autocomplete suggestions). */
		static inline const std::vector<Entry> ENTRIES =
		{
			/* Performance & timing stats. */
			{ "stat FPS",                  "",              "Show frame rate (FPS)" },
			{ "stat Unit",                 "",              "Frame/game/render/GPU times" },
			{ "stat UnitGraph",            "",              "Graph of unit frame times" },
			{ "stat UnitMax",              "",              "Peak unit frame times" },
			{ "stat Hitches",              "",              "Highlight frame hitches" },
			{ "stat NamedEvents",          "",              "Emit profiler named events" },
			{ "stat Summary",              "",              "General performance summary" },
			{ "stat Game",                 "",              "Gameplay tick timings", E_Requirement::Development },
			{ "stat Engine",               "",              "Engine frame timings", E_Requirement::Development },
			{ "stat SceneRendering",       "",              "Scene rendering breakdown", E_Requirement::Development },
			{ "stat GPU",                  "",              "GPU pass timings", E_Requirement::Development },
			{ "stat Memory",               "",              "Memory usage breakdown", E_Requirement::Development },
			{ "stat Levels",               "",              "Loaded & streaming levels" },
			{ "stat ColorList",            "",              "Named color reference", E_Requirement::Development },
			{ "stat AI",                   "",              "AI system timings" },
			{ "stat Anim",                 "",              "Animation timings", E_Requirement::Development },
			{ "stat Physics",              "",              "Physics simulation timings", E_Requirement::Development },
			{ "stat Audio",                "",              "Audio system stats", E_Requirement::Development },
			{ "stat ColorList",            "",              "List named engine colors" },
			{ "stat None",                 "",              "Hide all stat overlays", E_Requirement::Development },

			/* View modes & visualization. */
			{ "showdebug",                 "{category}",    "Toggle on-screen debug info", E_Requirement::Development },
			{ "viewmode Lit",              "",              "Default lit view", E_Requirement::Development },
			{ "viewmode Unlit",            "",              "Unlit view (no lighting)", E_Requirement::Development },
			{ "viewmode Wireframe",        "",              "Wireframe geometry view", E_Requirement::Development },
			{ "viewmode DetailLighting",   "",              "Detail lighting only", E_Requirement::Development },
			{ "viewmode LightComplexity",  "",              "Light overdraw heatmap", E_Requirement::Development },
			{ "viewmode ShaderComplexity", "",              "Shader cost heatmap", E_Requirement::Development },
			{ "prevviewmode",              "",              "Cycle to previous view mode" },
			{ "nextviewmode",              "",              "Cycle to next view mode" },
			{ "FreezeRendering",           "",              "Freeze render culling", E_Requirement::Development },

			/* Show flags: post processing. */
			{ "show PostProcessing",       "",              "Toggle all post processing" },
			{ "show Bloom",                "",              "Bloom" },
			{ "show LocalExposure",        "",              "Local exposure (UE 5.1+)" },
			{ "show Tonemapper",           "",              "Tonemapper" },
			{ "show ToneCurve",            "",              "Tonemapper tone curve" },
			{ "show EyeAdaptation",        "",              "Auto exposure" },
			{ "show ColorGrading",         "",              "Color grading" },
			{ "show AntiAliasing",         "",              "Anti-aliasing" },
			{ "show TemporalAA",           "",              "Temporal anti-aliasing" },
			{ "show ScreenPercentage",     "",              "Screen percentage upscale" },
			{ "show DepthOfField",         "",              "Depth of field" },
			{ "show MotionBlur",           "",              "Motion blur" },
			{ "show LensFlares",           "",              "Lens flares" },
			{ "show Vignette",             "",              "Vignette" },
			{ "show Grain",                "",              "Film grain" },
			{ "show SceneColorFringe",     "",              "Chromatic aberration" },
			{ "show CameraImperfections",  "",              "Bloom, flares, fringe, vignette" },
			{ "show AmbientCubemap",       "",              "Ambient cubemap" },
			{ "show LightShafts",          "",              "Light shafts" },
			{ "show PostProcessMaterial",  "",              "Post process materials" },
			{ "show SeparateTranslucency", "",              "Separate translucency pass" },
			{ "show Refraction",           "",              "Refraction" },
			{ "show DirectLighting",       "",              "Direct lighting" },
			{ "show DirectionalLights",    "",              "Directional lights" },
			{ "show PointLights",          "",              "Point lights" },
			{ "show SpotLights",           "",              "Spot lights" },
			{ "show RectLights",           "",              "Rect lights" },
			{ "show SkyLighting",          "",              "Sky light" },
			{ "show DeferredLighting",     "",              "Deferred lighting pass (UE5)" },
			{ "show GlobalIllumination",   "",              "Global illumination" },
			{ "show LumenGlobalIllumination", "",           "Lumen GI (UE 5.0+)" },
			{ "show LumenReflections",     "",              "Lumen reflections (UE 5.0+)" },
			{ "show ReflectionEnvironment", "",             "Reflection captures" },
			{ "show ScreenSpaceReflections", "",            "Screen space reflections" },
			{ "show AmbientOcclusion",     "",              "Screen space AO" },
			{ "show DistanceFieldAO",      "",              "Distance field AO" },
			{ "show DynamicShadows",       "",              "Dynamic shadows" },
			{ "show ContactShadows",       "",              "Contact shadows" },
			{ "show CapsuleShadows",       "",              "Capsule shadows" },
			{ "show RayTracedDistanceFieldShadows", "",     "Distance field shadows" },
			{ "show LightFunctions",       "",              "Light functions" },
			{ "show TexturedLightProfiles", "",             "IES light profiles" },
			{ "show VolumetricLightmap",   "",              "Volumetric lightmap" },
			{ "show IndirectLightingCache", "",             "Indirect lighting cache" },
			{ "show SubsurfaceScattering", "",              "Subsurface scattering" },
			{ "show Diffuse",              "",              "Diffuse lighting" },
			{ "show Specular",             "",              "Specular lighting" },
			{ "show PathTracing",          "",              "Path tracer (UE 4.22+, ray tracing)" },
			{ "show Rendering",            "",              "Toggle all world rendering" },
			{ "show StaticMeshes",         "",              "Static meshes" },
			{ "show SkeletalMeshes",       "",              "Skeletal meshes" },
			{ "show NaniteMeshes",         "",              "Nanite meshes (UE 5.0+)" },
			{ "show InstancedStaticMeshes", "",             "Instanced static meshes" },
			{ "show InstancedFoliage",     "",              "Foliage" },
			{ "show InstancedGrass",       "",              "Landscape grass" },
			{ "show Landscape",            "",              "Landscape" },
			{ "show BSP",                  "",              "BSP geometry" },
			{ "show Decals",               "",              "Decals" },
			{ "show Materials",            "",              "Materials (off = default)" },
			{ "show Translucency",         "",              "Translucency" },
			{ "show Particles",            "",              "Cascade particles" },
			{ "show Niagara",              "",              "Niagara particles" },
			{ "show HeterogeneousVolumes", "",              "Heterogeneous volumes (UE 5.2+)" },
			{ "show TextRender",           "",              "Text render components" },
			{ "show WidgetComponents",     "",              "3D widget components" },
			{ "show Paper2DSprites",       "",              "Paper2D sprites" },
			{ "show MediaPlanes",          "",              "Media planes" },
			{ "show DistanceCulledPrimitives", "",          "Draw distance-culled primitives" },
			{ "show PrecomputedVisibility", "",             "Precomputed visibility culling" },
			{ "show CameraInterpolation",  "",              "Camera interpolation" },
			{ "show StereoRendering",      "",              "Stereo (VR) rendering" },
			{ "show HMDDistortion",        "",              "HMD lens distortion" },
			{ "show Fog",                  "",              "Height fog" },
			{ "show VolumetricFog",        "",              "Volumetric fog" },
			{ "show Atmosphere",           "",              "Sky atmosphere" },
			{ "show Cloud",                "",              "Volumetric clouds" },
			{ "show Collision",            "",              "Collision shapes", E_Requirement::Development },
			{ "show CollisionPawn",        "",              "Pawn collision", E_Requirement::Development },
			{ "show CollisionVisibility",  "",              "Visibility collision", E_Requirement::Development },
			{ "show Bounds",               "",              "Primitive bounds", E_Requirement::Development },
			{ "show Wireframe",            "",              "Wireframe overlay", E_Requirement::Development },
			{ "show Volumes",              "",              "Volume actors", E_Requirement::Development },
			{ "show Splines",              "",              "Spline components", E_Requirement::Development },
			{ "show Constraints",          "",              "Physics constraints", E_Requirement::Development },
			{ "show MassProperties",       "",              "Physics mass properties", E_Requirement::Development },
			{ "show Navigation",           "",              "Navigation mesh", E_Requirement::Development },
			{ "show Brushes",              "",              "BSP brushes", E_Requirement::Development },
			{ "show BSPSplit",             "",              "BSP splits", E_Requirement::Development },
			{ "show BillboardSprites",     "",              "Editor sprites", E_Requirement::Development },
			{ "show Bones",                "",              "Skeletal bones", E_Requirement::Development },
			{ "show LOD",                  "",              "LOD transitions", E_Requirement::Development },
			{ "show LightRadius",          "",              "Light radius", E_Requirement::Development },
			{ "show LightInfluences",      "",              "Light influences", E_Requirement::Development },
			{ "show ShadowFrustums",       "",              "Shadow frustums", E_Requirement::Development },
			{ "show CameraFrustums",       "",              "Camera frustums", E_Requirement::Development },
			{ "show AudioRadius",          "",              "Audio radius", E_Requirement::Development },
			{ "show ForceFeedbackRadius",  "",              "Force feedback radius", E_Requirement::Development },
			{ "show StreamingBounds",      "",              "Texture streaming bounds", E_Requirement::Development },
			{ "show ShaderComplexity",     "",              "Shader cost heatmap", E_Requirement::Development },
			{ "show ShaderComplexityWithQuadOverdraw", "",  "Shader cost incl. quad overdraw", E_Requirement::Development },
			{ "show QuadOverdraw",         "",              "Quad overdraw", E_Requirement::Development },
			{ "show LightComplexity",      "",              "Light overdraw heatmap", E_Requirement::Development },
			{ "show StationaryLightOverlap", "",            "Stationary light overlap", E_Requirement::Development },
			{ "show LightMapDensity",      "",              "Lightmap density", E_Requirement::Development },
			{ "show LODColoration",        "",              "LOD coloration", E_Requirement::Development },
			{ "show HLODColoration",       "",              "HLOD coloration", E_Requirement::Development },
			{ "show LevelColoration",      "",              "Level coloration", E_Requirement::Development },
			{ "show PropertyColoration",   "",              "Property coloration", E_Requirement::Development },
			{ "show PrimitiveDistanceAccuracy", "",         "Primitive distance accuracy", E_Requirement::Development },
			{ "show MeshUVDensityAccuracy", "",             "Mesh UV density accuracy", E_Requirement::Development },
			{ "show MaterialTextureScaleAccuracy", "",      "Material texture scale accuracy", E_Requirement::Development },
			{ "show RequiredTextureResolution", "",         "Required texture resolution", E_Requirement::Development },
			{ "show VertexColors",         "",              "Vertex colors", E_Requirement::Development },
			{ "show GBufferHints",         "",              "GBuffer hints", E_Requirement::Development },
			{ "show PhysicalMaterialMasks", "",             "Physical material masks", E_Requirement::Development },
			{ "show VectorFields",         "",              "Vector fields", E_Requirement::Development },
			{ "show OnScreenDebug",        "",              "On-screen debug messages", E_Requirement::Development },
			{ "show DebugAI",              "",              "AI debug", E_Requirement::Development },
			{ "show VisLog",               "",              "Visual logger", E_Requirement::Development },
			{ "show GameplayDebug",        "",              "Gameplay debugger", E_Requirement::Development },
			{ "show VisualizeSenses",      "",              "AI perception senses", E_Requirement::Development },
			{ "show OcclusionMeshes",      "",              "Occlusion meshes", E_Requirement::Development },
			{ "show PrecomputedVisibilityCells", "",        "Visibility cells", E_Requirement::Development },
			{ "show VolumeLightingSamples", "",             "Volume lighting samples", E_Requirement::Development },
			{ "show HISMCOcclusionBounds", "",              "HISM occlusion bounds", E_Requirement::Development },
			{ "show HISMCClusterTree",     "",              "HISM cluster tree", E_Requirement::Development },
			{ "show PhysicsField",         "",              "Physics field", E_Requirement::Development },
			{ "show ServerDrawDebug",      "",              "Server debug draw", E_Requirement::Development },
			{ "show OverrideDiffuseAndSpecular", "",        "Override diffuse & specular", E_Requirement::Development },
			{ "show LightingOnlyOverride", "",              "Lighting only", E_Requirement::Development },
			{ "show ReflectionOverride",   "",              "Reflection override", E_Requirement::Development },
			{ "show TestImage",            "",              "Test image", E_Requirement::Development },
			{ "show RayTracingDebug",      "",              "Ray tracing debug", E_Requirement::Development },
			{ "show VirtualTexturePrimitives", "",          "Virtual texture primitives", E_Requirement::Development },
			{ "show VisualizeBuffer",      "",              "Buffer visualization", E_Requirement::Development },
			{ "show VisualizeHDR",         "",              "HDR histogram", E_Requirement::Development },
			{ "show VisualizeDOF",         "",              "Depth of field layers", E_Requirement::Development },
			{ "show VisualizeMotionBlur",  "",              "Motion blur vectors", E_Requirement::Development },
			{ "show VisualizeSSR",         "",              "SSR visualization", E_Requirement::Development },
			{ "show VisualizeSSS",         "",              "Subsurface visualization", E_Requirement::Development },
			{ "show VisualizeShadingModels", "",            "Shading models", E_Requirement::Development },
			{ "show VisualizeOutOfBoundsPixels", "",        "Out of bounds pixels", E_Requirement::Development },
			{ "show VisualizeLightCulling", "",             "Light culling", E_Requirement::Development },
			{ "show VisualizeDistanceFieldAO", "",          "Distance field AO", E_Requirement::Development },
			{ "show VisualizeMeshDistanceFields", "",       "Mesh distance fields", E_Requirement::Development },
			{ "show VisualizeGlobalDistanceField", "",      "Global distance field", E_Requirement::Development },
			{ "show VisualizeVolumetricLightmap", "",       "Volumetric lightmap samples", E_Requirement::Development },
			{ "show VisualizeSkyAtmosphere", "",            "Sky atmosphere", E_Requirement::Development },
			{ "show VisualizeGPUSkinCache", "",             "GPU skin cache", E_Requirement::Development },
			{ "show VisualizeNanite",      "",              "Nanite visualization (UE 5.0+)", E_Requirement::Development },
			{ "show VisualizeLumen",       "",              "Lumen visualization (UE 5.0+)", E_Requirement::Development },
			{ "show VisualizeVirtualShadowMap", "",         "Virtual shadow maps (UE 5.0+)", E_Requirement::Development },

			/* Rendering cvars. */
			{ "r.ShadowQuality",           "{int}",         "Shadow quality (0-5)" },
			{ "r.ScreenPercentage",        "{float}",       "Render resolution scale %" },
			{ "r.Color.Mid",               "{float}",       "Color grading midtones" },
			{ "r.VSync",                   "{int}",         "Vertical sync (0/1)" },
			{ "r.SetRes",                  "{WxH[f|w|wf]}", "Set resolution and mode" },
			{ "r.ViewDistanceScale",       "{float}",       "Draw distance multiplier" },
			{ "r.StaticMeshLODDistanceScale", "{float}",    "Static mesh LOD distance" },
			{ "r.SkeletalMeshLODBias",     "{int}",         "Skeletal mesh LOD bias" },
			{ "r.MipMapLODBias",           "{float}",       "Texture mip bias" },
			{ "r.MaxAnisotropy",           "{0-16}",        "Anisotropic filtering" },
			{ "r.Streaming.PoolSize",      "{MB}",          "Texture streaming pool" },
			{ "r.PostProcessAAQuality",    "{0-6}",         "Post process AA quality" },
			{ "r.AntiAliasingMethod",      "{0-4}",         "AA method: none/FXAA/TAA/MSAA/TSR (UE 5.0+)" },
			{ "r.MotionBlurQuality",       "{0-4}",         "Motion blur quality" },
			{ "r.DepthOfFieldQuality",     "{0-4}",         "Depth of field quality" },
			{ "r.BloomQuality",            "{0-5}",         "Bloom quality" },
			{ "r.AmbientOcclusionLevels",  "{0-4}",         "SSAO levels" },
			{ "r.SSR.Quality",             "{0-4}",         "Screen space reflections quality" },
			{ "r.SceneColorFringeQuality", "{0|1}",         "Chromatic aberration" },
			{ "r.Tonemapper.Sharpen",      "{float}",       "Image sharpening" },
			{ "r.Tonemapper.GrainQuantization", "{0|1}",    "Grain dithering" },
			{ "r.EyeAdaptationQuality",    "{0-3}",         "Auto exposure quality" },
			{ "r.Shadow.MaxResolution",    "{int}",         "Max shadow map resolution" },
			{ "r.Shadow.DistanceScale",    "{float}",       "Shadow distance multiplier" },
			{ "r.LightShaftQuality",       "{0|1}",         "Light shafts" },
			{ "r.Fog",                     "{0|1}",         "Height fog" },
			{ "r.VolumetricFog",           "{0|1}",         "Volumetric fog" },
			{ "r.DefaultFeature.MotionBlur", "{0|1}",       "Default motion blur" },
			{ "r.DefaultFeature.AutoExposure", "{0|1}",     "Default auto exposure" },
			{ "foliage.DensityScale",      "{float}",       "Foliage density" },
			{ "grass.DensityScale",        "{float}",       "Landscape grass density" },
			{ "r.DynamicGlobalIlluminationMethod", "{0-2}", "GI method: none/Lumen/SSGI (UE 5.0+)" },
			{ "r.ReflectionMethod",        "{0-2}",         "Reflections: none/Lumen/SSR (UE 5.0+)" },
			{ "r.Nanite",                  "{0|1}",         "Nanite rendering (UE 5.0+)" },
			{ "r.FullScreenMode",          "{0-2}",         "Fullscreen / windowed fullscreen / windowed" },
			{ "t.IdleWhenNotForeground",   "{0|1}",         "Throttle when unfocused" },
			{ "gamma",                     "{float}",       "Display gamma" },
			{ "t.MaxFPS",                  "{float}",       "Frame rate cap" },

			/* Camera & gameplay debug. */
			{ "fov",                       "{degrees}",     "Set camera field of view" },
			{ "slomo",                     "{scale}",       "Set global time scale", E_Requirement::CheatManager },
			{ "demospeed",                 "{scale}",       "Replay playback speed" },
			{ "pause",                     "",              "Toggle game pause" },
			{ "ToggleDebugCamera",         "",              "Detach free debug camera", E_Requirement::CheatManager },
			{ "BugIt",                     "",              "Dump camera transform", E_Requirement::CheatManager | E_Requirement::Development },
			{ "BugItGo",                   "{x} {y} {z} {pitch} {yaw} {roll}", "Teleport to coordinates", E_Requirement::CheatManager },
			{ "Teleport",                  "",              "Teleport to trace hit", E_Requirement::CheatManager },
			{ "God",                       "",              "Toggle god mode", E_Requirement::CheatManager | E_Requirement::Development },
			{ "Ghost",                     "",              "Noclip free movement", E_Requirement::CheatManager | E_Requirement::Development },
			{ "Fly",                       "",              "Enable flying", E_Requirement::CheatManager | E_Requirement::Development },
			{ "Walk",                      "",              "Return to walking", E_Requirement::CheatManager | E_Requirement::Development },
			{ "PlayersOnly",               "",              "Freeze everything but players", E_Requirement::CheatManager | E_Requirement::Development },
			{ "ChangeSize",                "{scale}",       "Scale player character", E_Requirement::CheatManager | E_Requirement::Development },
			{ "Summon",                    "{class}",       "Spawn actor of class", E_Requirement::CheatManager | E_Requirement::Development },
			{ "DestroyTarget",             "",              "Destroy actor in crosshair", E_Requirement::CheatManager | E_Requirement::Development },
			{ "DestroyAll",                "{class}",       "Destroy all actors of class", E_Requirement::CheatManager | E_Requirement::Development },
			{ "DestroyPawns",              "",              "Destroy all non-player pawns", E_Requirement::CheatManager | E_Requirement::Development },
			{ "DamageTarget",              "{amount}",      "Damage actor in crosshair", E_Requirement::CheatManager | E_Requirement::Development },
			{ "FreezeFrame",               "{delay}",       "Pause after delay", E_Requirement::CheatManager | E_Requirement::Development },
			{ "ViewSelf",                  "",              "View from own pawn", E_Requirement::CheatManager | E_Requirement::Development },
			{ "ViewPlayer",                "{name}",        "View from player", E_Requirement::CheatManager | E_Requirement::Development },
			{ "ViewActor",                 "{name}",        "View from actor", E_Requirement::CheatManager | E_Requirement::Development },
			{ "ViewClass",                 "{class}",       "Cycle view through class", E_Requirement::CheatManager | E_Requirement::Development },
			{ "StreamLevelIn",             "{level}",       "Load streaming level", E_Requirement::CheatManager | E_Requirement::Development },
			{ "StreamLevelOut",            "{level}",       "Unload streaming level", E_Requirement::CheatManager | E_Requirement::Development },
			{ "ToggleAILogging",           "",              "AI logging", E_Requirement::CheatManager | E_Requirement::Development },

			/* World & session. */
			{ "open",                      "{map}",				"Load map" },
			{ "servertravel",              "{map}",				"Server travel to map" },
			{ "disconnect",                "",					"Leave current session" },
			{ "reconnect",                 "",					"Reconnect to last server" },
			{ "RestartLevel",              "",					"Restart current level" },
			{ "ce",                        "{event}",			"Call level Blueprint custom event" },
			{ "HighResShot",               "{multiplier|WxH}",  "High resolution screenshot" },
			{ "shot",                      "",					"Screenshot" },
			{ "showhud",                   "",					"Toggle HUD" },
			{ "fullscreen",                "",					"Toggle fullscreen" },
			{ "gamever",                   "",					"Print game version" },

			/* Inspection & profiling. */
			{ "getall",                    "{class} {property}", "Print property of all objects", E_Requirement::Development },
			{ "set",                       "{class} {property} {value}", "Set property on class objects", E_Requirement::Development },
			{ "DisplayAll",                "{class} {property}", "Show property on screen", E_Requirement::Development },
			{ "DisplayAllLocation",        "{class}",       "Show locations on screen", E_Requirement::Development },
			{ "DisplayAllRotation",        "{class}",       "Show rotations on screen", E_Requirement::Development },
			{ "DisplayClear",              "",              "Clear on-screen displays", E_Requirement::Development },
			{ "obj gc",                    "",              "Force garbage collection" },
			{ "memreport",                 "{-full}",       "Memory report to file", E_Requirement::Development },
			{ "DumpTicks",                 "",              "List ticking objects", E_Requirement::Development },
			{ "ListTextures",              "",              "List loaded textures", E_Requirement::Development },
			{ "ProfileGPU",                "",              "GPU profile of one frame", E_Requirement::Development },
			{ "showlog",                   "",              "Open log window", E_Requirement::Development },

			/* Utility. */
			{ "DumpConsoleCommands",       "",              "List all console commands", E_Requirement::Development },
			{ "DisableAllScreenMessages",  "",              "Hide on-screen messages", E_Requirement::Development },
			{ "obj list",                  "{class}",       "List loaded objects by class", E_Requirement::Development },
			{ "quit",                      "",              "Exit the game" },
			{ "exit",                      "",              "Exit the game" },
		};

		/* Returns entries whose command starts with the given prefix (case insensitive). Empty prefix yields nothing. */
		static std::vector<const Entry*> Match(const std::string& prefix);
	};




	class ConsoleCustomCommands
	{
	public:
		using Handler = bool (*)(const std::vector<std::string>& arguments);

		struct Command
		{
			std::string name;
			std::string hint;
			std::string description;
			Handler handler; // Implementation inside UETools-GUI.
		};

	private:
		static bool FpsMax(const std::vector<std::string>& arguments);
		static bool HostTimescale(const std::vector<std::string>& arguments);
		static bool Noclip(const std::vector<std::string>& arguments);
		static bool Restart(const std::vector<std::string>& arguments);
		static bool Ghost(const std::vector<std::string>& arguments);
		static bool Fly(const std::vector<std::string>& arguments);
		static bool Walk(const std::vector<std::string>& arguments);
		static bool Bind(const std::vector<std::string>& arguments);
		static bool BindToggle(const std::vector<std::string>& arguments);
		static bool UnBind(const std::vector<std::string>& arguments);
		static bool SoftSummon(const std::vector<std::string>& arguments);
		static bool SoftConstruct(const std::vector<std::string>& arguments);

	public:
		/* Commands handled by UETools itself (Source-style names for convenience). */
		static inline const std::vector<Command> COMMANDS =
		{
			{ "fps_max",        "{float}", "Frame rate cap", &FpsMax },
			{ "host_timescale", "{float}", "Global time scale", &HostTimescale },
			{ "noclip",			"", "Noclip free movement", &Noclip },
			{ "tcl",			"", "Noclip free movement", &Noclip },
			{ "restart",		"", "Restart current level", &Restart },
			{ "GhostC",			"", "Noclip free movement", &Ghost },
			{ "FlyC",			"", "Enable flying", &Fly },
			{ "WalkC",			"", "Return to walking", &Walk },
			{ "Bind",           "{key} {command} [{release command}]", "Bind key to command(s)", &Bind },
			{ "BindToggle",     "{key} {command 1} {command 2}", "Alternate two commands on key press", &BindToggle },
			{ "UnBind",         "{key}", "Remove key binding", &UnBind },
#ifdef SOFT_PATH
			{ "SoftSummon",     "{actor path}", "Spawn actor from path", &SoftSummon },
			{ "SoftConstruct",  "{object path}", "Construct object from path", &SoftConstruct },
#endif
		};

		/* Case-insensitive lookup by command name. */
		static const Command* Find(const std::string& name);

		/* Checks if command is custom and runs it, rest is redirected to title. */
		static bool Execute(const std::string& commandLine);

		/* Splits by whitespace; "quoted text" is a single token (keeps spaces & "|"). */
		static std::vector<std::string> Tokenize(const std::string& text);
	};




	class BootlegConsole
	{
	public:
		struct Suggestion
		{
			std::string insertText;
			std::string displayText;
			std::string description;
			bool fromHistory = false;
			ConsoleDictionary::E_Requirement requirements = ConsoleDictionary::E_Requirement::None;
			bool isCustom = false;
		};

		/* Allocate large buffer to account for combined console commands (e.g: "stat fps | stat unit") */
		static inline const size_t bufferSize = SIZE_BUFFER_CONSOLE;
		static inline char buffer[bufferSize] = {};

		/* Previously executed commands, most recent first (Unreal-style input history). */
		static inline std::vector<std::string> history;

		/* Autocomplete / history runtime state. */
		static inline std::vector<Suggestion> suggestions;
		static inline int suggestionIndex = -1; // Highlighted suggestion (-1 = none selected yet).
		static inline bool suggestionsDirty = true; // Recompute suggestions from the buffer on the next frame.
		static inline bool suggestionsVisible = false; // Whether the dropdown should be drawn this frame.
		static inline bool suggestionsKeepOpen = false; // Keep the dropdown alive while it's hovered (set by DrawSuggestions).
		static inline ImGuiID inputId = 0; // ID of the console input (used to re-activate it after a click).
		static inline bool moveCursorToEnd = false; // Place the caret at the end once the input is re-activated.
		static inline ImVec2 suggestionsAnchor = {}; // Top-left screen position for the dropdown.
		static inline float suggestionsWidth = 0.0f; // Width of the dropdown (matches the input).

		static void RefreshSuggestions();
		static void AddHistory(const std::string& command);
		static void LoadHistory();
		static void SaveHistory();
	};




	class Bindings
	{
	public:
		enum class E_BindMode : uint8_t
		{
			Press,          // Command on key press.
			PressRelease,   // Command #1 on press, #2 on release.
			Toggle          // Commands #1 / #2 on alternating presses.
		};

		struct Binding
		{
			ImGuiKey key;
			E_BindMode mode;
			std::string commandA;   // Press / first toggle command.
			std::string commandB;   // Release / second toggle command ("" for Press).
			bool isDown;            // Key state on previous poll.
			bool toggleState;       // Toggle: next press runs commandB.
		};

		/* "Bindings" menu form. */
		static inline ImGui::KeyBinding formKey;
		static inline int32_t formMode = 0;
		static inline const size_t formCommandSize = SIZE_BUFFER_CONSOLE;
		static inline char formCommandA[formCommandSize] = {};
		static inline char formCommandB[formCommandSize] = {};

		static const char* GetModeName(E_BindMode mode);
		static ImGuiKey ParseKey(const std::string& name);

		/* Binding an already bound key replaces it. */
		static bool Set(ImGuiKey key, E_BindMode mode, const std::string& commandA, const std::string& commandB);
		static bool Remove(ImGuiKey key);
		static std::vector<Binding> GetAll();

		static void Poll();             // Keybindings worker thread: detects key transitions, queues commands.
		static void ExecuteQueued();    // Render thread: runs queued commands.

		static void Load();
		static void Save();

	private:
		static inline std::mutex mutex;
		static inline std::vector<Binding> bindings;
		static inline std::vector<std::string> queue;
		static inline bool isLoading = false;

		static std::string ToCommandLine(const Binding& binding);
	};




	class Overlays
	{
	public:
		static inline bool showCharacter = false;

		static void Draw();
		static void Draw_ThreadSafe();
	};
};






namespace BackgroundTasks
{
	class KeybindingsHandler
	{
	private:
		static inline std::atomic<bool> isEnabled = false;

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
		static inline std::atomic<bool> isEnabled = false;

		static inline float& delay = Features::DirectionalMovement::delay;

		static inline HANDLE thread = nullptr;
		static void Worker();

	public:
		static void Enable();
		static void Disable();
	};

	class SoundPlayer
	{
	private:
		static inline std::atomic<bool> isEnabled = false;

		/* Pending sound packed as (frequency << 16) | duration; 0 if there's none. */
		static inline std::atomic<uint32_t> pendingSound = 0;

		static inline float delay = 0.01f;

		static inline HANDLE thread = nullptr;
		static void Worker();

	public:
		static void Play(uint16_t frequency, uint16_t duration);

		static void Enable();
		static void Disable();
	};

#ifdef TASK_CONSTRUCT_CONSOLE
	class ConstructConsole
	{
	private:
		static inline std::atomic<bool> isEnabled = false;

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
		static inline std::atomic<bool> isEnabled = false;

		static inline bool cheatManagerConstructed = false;

		static inline float delay = 1.0f;

		static inline HANDLE thread = nullptr;
		static void Worker();

	public:
		static void Enable();
		static void Disable();
	};
#endif

	void Init();
	void Shutdown();
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
		static inline ImGui::KeyBinding general_Unload;


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






class DebugDraw
{
public:
	struct Style
	{
		uint32_t lineColor;
		float lineThickness;
		bool fill;          // Fill the projected silhouette (bones: filled kites) with a translucent line color.
		float fillOpacity;  // Fill alpha relative to the line color alpha.
	};

	static void DrawBounds(const SDK::FVector& center, const SDK::FVector& halfExtent, const Style& style);

private:
	struct View
	{
		SDK::APlayerController* playerController;
		SDK::FVector cameraLocation;
		SDK::FVector cameraForward;
	};

	static bool GetView(View* outView);
	static float GetDepth(const View& view, const SDK::FVector& worldLocation);
	static bool ProjectPoint(const View& view, const SDK::FVector& worldLocation, ImVec2* outScreenLocation);
	static uint32_t GetFillColor(const Style& style);

	static void DrawSegment(const View& view, ImDrawList* drawList, const SDK::FVector& start, const SDK::FVector& end, uint32_t color, float thickness);
	static void DrawPath(const View& view, ImDrawList* drawList, const std::vector<SDK::FVector>& points, bool closed, uint32_t color, float thickness);
	static void DrawJoints(const View& view, ImDrawList* drawList, const std::vector<SDK::FVector>& points, const Style& style);
	static void DrawFill(const View& view, ImDrawList* drawList, const std::vector<SDK::FVector>& points, const Style& style);
	static void DrawBone(const View& view, ImDrawList* drawList, const SDK::FVector& parentLocation, const SDK::FVector& childLocation, const Style& style);

	static void DrawOrientedBox(const View& view, ImDrawList* drawList, const SDK::FVector& center, const SDK::FVector& axisX, const SDK::FVector& axisY, const SDK::FVector& axisZ, const SDK::FVector& halfExtent, const Style& style);
	static void DrawOrientedSphere(const View& view, ImDrawList* drawList, const SDK::FVector& center, const SDK::FVector& axisX, const SDK::FVector& axisY, const SDK::FVector& axisZ, float radius, const Style& style);
	static void DrawOrientedCapsule(const View& view, ImDrawList* drawList, const SDK::FVector& center, const SDK::FVector& axisUp, float radius, float halfHeight, const Style& style);

#ifdef COLLISION_VISUALIZER
	struct ConvexShape
	{
		int32_t vertexCount;
		std::vector<std::pair<int32_t, int32_t>> featureEdges;
	};

	struct SkeletonBone
	{
		SDK::FName name;
		int32_t parentIndex;
	};

	struct SkeletonShape
	{
		int32_t socketCount;
		bool allSockets;
		std::vector<SkeletonBone> bones;
	};

	static inline std::unordered_map<SDK::FKConvexElem*, ConvexShape> convexCache;
	static inline std::unordered_map<SDK::USkeletalMeshComponent*, SkeletonShape> skeletonCache;

	static const ConvexShape& GetConvexShape(SDK::FKConvexElem* convexElement);
	static const SkeletonShape& GetSkeletonShape(SDK::USkeletalMeshComponent* skeletalMeshComponent, bool drawAllSockets);

public:
	static void DrawConvexElement(SDK::FKConvexElem* convexElement, const Unreal::Transform& componentTransform, const Style& style);

	static void DrawBodySetup(SDK::UBodySetup* bodySetup, const Unreal::Transform& componentTransform, const Style& style);
	static void DrawVolume(SDK::AVolume* volume, const Style& style);

	static void DrawStaticMeshComponent(SDK::UStaticMeshComponent* staticMeshComponent, const Style& style);
	static void DrawInstancedStaticMeshComponent(SDK::UInstancedStaticMeshComponent* instancedStaticMeshComponent, const Style& style);

	static void DrawSkeletalMeshComponent(SDK::USkeletalMeshComponent* skeletalMeshComponent, bool drawAllSockets, const Style& style);

	static void DrawCapsuleComponent(SDK::UCapsuleComponent* capsuleComponent, const Style& style);
	static void DrawSphereComponent(SDK::USphereComponent* sphereComponent, const Style& style);
	static void DrawBoxComponent(SDK::UBoxComponent* boxComponent, const Style& style);
	static void DrawSplineComponent(SDK::USplineComponent* splineComponent, const Style& style);
#endif
};






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

#ifdef OBJECT_PROPERTIES
	class Properties
	{
	public:
		static void Draw(SDK::UObject* objectReference);
	};
#endif

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

		class Bindings
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
			static void DrawSuggestions();
		};
	};
}