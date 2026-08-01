#include "GUI.h"






// ==============================
// |          #ImGui			|
// ==============================
ImGui::Viewport ImGui::GetViewport()
{
	ImGui::Viewport viewport;

	ImGuiViewport* iViewport = ImGui::GetMainViewport();
	if (iViewport == nullptr)
		return viewport;

	viewport.iViewport = iViewport;
	viewport.iViewportPosition = { iViewport->Pos.x, iViewport->Pos.y };
	viewport.iViewportSize = { iViewport->Size.x, iViewport->Size.y };

	return viewport;
}


ImDrawList* ImGui::GetDrawList()
{
	ImDrawList* iDrawList = ImGui::GetBackgroundDrawList();
	return iDrawList ? iDrawList : nullptr;
}




bool ImGui::Texture2D::Exists(const std::string& textureName)
{
	return ImTextures.contains(textureName);
}

bool ImGui::Texture2D::Exists(const Window::TextureMetaData& textureMetaData)
{
	return Exists(textureMetaData.name);
}


ImTextureID ImGui::Texture2D::Get(const std::string& textureName)
{
	auto textureIterator = ImTextures.find(textureName);

	if (textureIterator == ImTextures.end())
		return (ImTextureID)0;

	return textureIterator->second;
}

ImTextureID ImGui::Texture2D::Get(const Window::TextureMetaData& textureMetaData)
{
	return Get(textureMetaData.name);
}


void ImGui::Texture2D::Add(const std::string& textureName, ImTextureID iTextureId)
{
	if (ImTextures.contains(textureName))
		return;

	ImTextures.emplace(textureName, iTextureId);
}

void ImGui::Texture2D::Add(const Window::TextureMetaData& textureMetaData, ImTextureID iTextureId)
{
	return Add(textureMetaData.name, iTextureId);
}


bool ImGui::Texture2D::IsValid(const ImTextureID& iTextureId)
{
	return iTextureId != (ImTextureID)0;
}


bool ImGui::IconButton(const char* textureName, const char* text, const ImVec2& size)
{
	bool isPressed = false;

	ImTextureID iconTexture = ImGui::Texture2D::Get(textureName);
	ImGui::PushID(text);

	if (ImGui::Texture2D::IsValid(iconTexture))
	{
		isPressed = ImGui::ImageButton("##icon_button", iconTexture, size);
	}
	else
	{
		ImVec2 padding = ImGui::GetStyle().FramePadding;
		ImVec2 totalSize = ImVec2
		(
			size.x + padding.x * 2.0f,
			size.y + padding.y * 2.0f
		);

		isPressed = ImGui::Button("X", totalSize);
	}

	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::TextUnformatted(text);
		ImGui::EndTooltip();
	}

	ImGui::PopID();

	return isPressed;
}

bool ImGui::IconButton(const Window::TextureMetaData& textureMetaData, const char* text, const ImVec2& size)
{
	return IconButton(textureMetaData.name, text, size);
}




void ImGui::TextBool(const char* label, bool inBool, const char* text_true, const char* text_false, bool useColoring, ImU32 color_true, ImU32 color_false)
{
	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	if (useColoring)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, inBool ? color_true : color_false);
		ImGui::TextUnformatted(inBool
			? (text_true ? text_true : "True")
			: (text_false ? text_false : "False"));
		ImGui::PopStyleColor();
	}
	else
		ImGui::TextUnformatted(inBool
			? (text_true ? text_true : "True")
			: (text_false ? text_false : "False"));

}

void ImGui::TextBool(const char* label, bool inBool)
{
	TextBool(label, inBool, "True", "False", false, ImU32(), ImU32());
}

void ImGui::TextBoolColored(const char* label, bool status)
{
	TextBool(label, status, "True", "False", true, ImGui::Color::Green, ImGui::Color::Red);
}

void ImGui::TextBoolPresence(const char* label, bool presence)
{
	TextBool(label, presence, "Is Present", "Doesn't Exist!", false, ImU32(), ImU32());
}

void ImGui::TextBoolPresenceColored(const char* label, bool presence)
{
	TextBool(label, presence, "Is Present", "Doesn't Exist!", true, ImGui::Color::Green, ImGui::Color::Red);
}

void ImGui::TextBoolMultiplePresence(const char* label, bool presence)
{
	TextBool(label, presence, "Are Present", "Are Non Existent!", false, ImU32(), ImU32());
}

void ImGui::TextBoolMultiplePresenceColored(const char* label, bool presence)
{
	TextBool(label, presence, "Are Present", "Are Non Existent!", true, ImGui::Color::Green, ImGui::Color::Red);
}




void ImGui::TextFloat(const char* label, const float value, bool useColoring, ImU32 color_positive, ImU32 color_negative)
{
	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	if (useColoring && value != 0.0f)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, value > 0.0f ? color_positive : color_negative);
		ImGui::Text("%f", value);
		ImGui::PopStyleColor();;
	}
	else
		ImGui::Text("%f", value);
}

void ImGui::TextFloat(const char* label, const float value)
{
	TextFloat(label, value, false, ImU32(), ImU32());
}

void ImGui::TextFloatColored(const char* label, const float value)
{
	TextFloat(label, value, true, ImGui::Color::Green, ImGui::Color::Red);
}




void ImGui::TextInt(const char* label, int32_t value, bool useColoring, ImU32 color_positive, ImU32 color_negative)
{
	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	if (useColoring && value != 0)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, value > 0.0f ? color_positive : color_negative);
		ImGui::Text("%d", value);
		ImGui::PopStyleColor();;
	}
	else
		ImGui::Text("%d", value);
}

void ImGui::TextInt(const char* label, int32_t value)
{
	TextInt(label, value, false, ImU32(), ImU32());
}

void ImGui::TextIntColored(const char* label, int32_t value)
{
	TextInt(label, value, true, ImGui::Color::Green, ImGui::Color::Red);
}




void ImGui::TextVector(const char* label, const SDK::FVector& value, bool useColoring, ImU32 color_positive, ImU32 color_negative)
{
	constexpr ImU32 axis_colors[3]
	{
		IM_COL32(255, 0, 0, 255),
		IM_COL32(0, 255, 0, 255),
		IM_COL32(0, 0, 255, 255)
	};

	constexpr const char* axis_prefixes[3]
	{
		"X:",
		"Y:",
		"Z:"
	};

	const double coords[3]
	{
		value.X,
		value.Y,
		value.Z
	};

	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	std::string vectorString = std::format("X: {:.3f} Y: {:.3f} Z: {:.3f}", coords[0], coords[1], coords[2]);
	ImGui::PushID(label ? label : vectorString.c_str());

	ImGui::BeginGroup();
	for (int i = 0; i < 3; i++)
	{
		if (useColoring) ImGui::PushStyleColor(ImGuiCol_Text, axis_colors[i]);
		ImGui::SetFontBig();
		ImGui::TextUnformatted(axis_prefixes[i]);
		ImGui::SetFontRegular();
		if (useColoring) ImGui::PopStyleColor();

		ImGui::SameLine();

		bool neutralValue = coords[i] > -0.0000001 && coords[i] < 0.0000001;
		if (useColoring && !neutralValue) ImGui::PushStyleColor(ImGuiCol_Text, coords[i] > 0.0 ? color_positive : color_negative);
		ImGui::Text("%.3f", neutralValue ? 0.0 : coords[i]);
		if (useColoring && !neutralValue) ImGui::PopStyleColor();

		if (i != 2)
		{
			ImGui::SameLine();
			ImGui::Spacing();
			ImGui::SameLine();
		}
	}
	ImGui::EndGroup();

	if (ImGui::BeginPopupContextItem("##VectorContextMenu", ImGuiPopupFlags_MouseButtonRight))
	{
		if (ImGui::Selectable("Copy"))
		{
			GUI::PlayActionSound(Utilities::Clipboard::SetText(vectorString.c_str()));
		}
		ImGui::EndPopup();
	}

	ImGui::PopID();
}

void ImGui::TextVector(const char* label, const SDK::FVector& value)
{
	TextVector(label, value, false, ImU32(), ImU32());
}

void ImGui::TextVectorColored(const char* label, const SDK::FVector& value)
{
	TextVector(label, value, true, ImGui::Color::Green, ImGui::Color::Red);
}




void ImGui::TextRotator(const char* label, const SDK::FRotator& value, bool useColoring, ImU32 color_positive, ImU32 color_negative)
{
	constexpr ImU32 axis_colors[3]
	{
		IM_COL32(255, 0, 0, 255),
		IM_COL32(0, 255, 0, 255),
		IM_COL32(0, 0, 255, 255)
	};

	constexpr const char* axis_prefixes[3]
	{
		"Pitch:",
		"Yaw:",
		"Roll:"
	};

	const double angles[3]
	{
		value.Pitch,
		value.Yaw,
		value.Roll
	};

	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	std::string rotatorString = std::format("Pitch: {:.3f} Yaw: {:.3f} Roll: {:.3f}", angles[0], angles[1], angles[2]);
	ImGui::PushID(label ? label : rotatorString.c_str());

	ImGui::BeginGroup();
	for (int i = 0; i < 3; i++)
	{
		if (useColoring) ImGui::PushStyleColor(ImGuiCol_Text, axis_colors[i]);
		ImGui::SetFontBig();
		ImGui::TextUnformatted(axis_prefixes[i]);
		ImGui::SetFontRegular();
		if (useColoring) ImGui::PopStyleColor();

		ImGui::SameLine();

		bool neutralValue = angles[i] > -0.0000001 && angles[i] < 0.0000001;
		if (useColoring && !neutralValue) ImGui::PushStyleColor(ImGuiCol_Text, angles[i] > 0.0 ? color_positive : color_negative);
		ImGui::Text("%.3f", neutralValue ? 0.0 : angles[i]);
		if (useColoring && !neutralValue) ImGui::PopStyleColor();

		if (i != 2)
		{
			ImGui::SameLine();
			ImGui::Spacing();
			ImGui::SameLine();
		}
	}
	ImGui::EndGroup();

	if (ImGui::BeginPopupContextItem("##RotatorContextMenu", ImGuiPopupFlags_MouseButtonRight))
	{
		if (ImGui::Selectable("Copy"))
		{
			GUI::PlayActionSound(Utilities::Clipboard::SetText(rotatorString.c_str()));
		}
		ImGui::EndPopup();
	}

	ImGui::PopID();
}

void ImGui::TextRotator(const char* label, const SDK::FRotator& value)
{
	TextRotator(label, value, false, ImU32(), ImU32());
}

void ImGui::TextRotatorColored(const char* label, const SDK::FRotator& value)
{
	TextRotator(label, value, true, ImGui::Color::Green, ImGui::Color::Red);
}




void ImGui::AddHint(const char* hint)
{
	ImGui::BeginTooltip();
	ImGui::TextUnformatted(hint);
	ImGui::EndTooltip();
}

void ImGui::AddHint_OnItemHovered(const char* hint)
{
	if (ImGui::IsItemHovered())
		AddHint(hint);
}

void ImGui::AddHint_OnItemFocused(const char* hint)
{
	if (ImGui::IsItemFocused())
		AddHint(hint);
}

void ImGui::AddHint_OnItemActive(const char* hint)
{
	if (ImGui::IsItemActive())
		AddHint(hint);
}

void ImGui::AddHint_OnItemEdited(const char* hint)
{
	if (ImGui::IsItemEdited())
		AddHint(hint);
}

void ImGui::QuestionMarkHint(const char* hint)
{
	ImGui::TextDisabled("(?)");
	AddHint_OnItemHovered(hint);
}




void ImGui::TextCopyable(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	char buffer[2048];
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);

	ImVec2 labelPos = ImGui::GetCursorScreenPos();
	ImVec2 labelSize = ImGui::CalcTextSize(buffer);

	static const ImVec2 bgPadding(2.0f, 1.0f);
	ImVec2 bgMinPos = ImVec2(labelPos.x - bgPadding.x, labelPos.y - bgPadding.y);
	ImVec2 bgMaxPos = ImVec2(labelPos.x + labelSize.x + bgPadding.x, labelPos.y + labelSize.y + bgPadding.y);
	static ImU32 bgColor = IM_COL32(0, 0, 20, 75);
	ImGui::GetWindowDrawList()->AddRectFilled(bgMinPos, bgMaxPos, bgColor, 2.0f);

	ImGui::TextUnformatted(buffer);
	ImGui::PushID(buffer);

	if (ImGui::BeginPopupContextItem("##CopyContextMenu"))
	{
		if (ImGui::Selectable("Copy"))
		{
			GUI::PlayActionSound(Utilities::Clipboard::SetText(buffer));
		}
		ImGui::EndPopup();
	}

	ImGui::PopID();
}




void ImGui::ReadOnlyInputText(const char* label, const char* text, bool showCopyButton)
{
	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	ImGui::PushID(label ? label : (text ? text : "ReadOnlyInputText"));
	const size_t length = text ? strlen(text) : 0;

	std::string buffer(text ? text : "");
	ImGui::InputText("##ReadOnlyInputText", buffer.data(), buffer.size() + 1, ImGuiInputTextFlags_ReadOnly);
	if (showCopyButton)
	{
		ImGui::SameLine();
		if (ImGui::Button("Copy"))
		{
			GUI::PlayActionSound(Utilities::Clipboard::SetText(buffer.data()));
		}
	}

	ImGui::PopID();
}




bool ImGui::SliderIntEditable(const char* label, int32_t* v, int32_t v_min, int32_t v_max, const char* format, ImGuiSliderFlags flags)
{
	ImGuiID id = ImGui::GetID(label);
	ImGuiStorage* storage = ImGui::GetStateStorage();

	bool isEditing = storage->GetBool(id, false);
	bool valueChanged = false;

	if (isEditing)
	{
		bool wasFocused = storage->GetBool(id + 2, false);
		if (wasFocused == false)
		{
			ImGui::SetKeyboardFocusHere();
			storage->SetBool(id + 2, true);
		}

		ImGui::PushID("Edit");
		valueChanged = ImGui::InputInt(label, v, 0, 0, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll);
		ImGui::PopID();

		if (ImGui::IsItemDeactivated() || (ImGui::IsItemHovered() == false && ImGui::IsMouseClicked(ImGuiMouseButton_Left)))
		{
			storage->SetBool(id, false);
			storage->SetBool(id + 2, false);
		}
	}
	else
	{
		valueChanged = ImGui::SliderScalar(label, ImGuiDataType_S32, v, &v_min, &v_max, format, flags);

		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::Selectable("Manual Edit"))
			{
				storage->SetBool(id, true);
			}
			ImGui::EndPopup();
		}
	}

	return valueChanged;
}

bool ImGui::SliderFloatEditable(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
	ImGuiID id = ImGui::GetID(label);
	ImGuiStorage* storage = ImGui::GetStateStorage();

	bool isEditing = storage->GetBool(id, false);
	bool valueChanged = false;

	if (isEditing)
	{
		bool wasFocused = storage->GetBool(id + 2, false);
		if (wasFocused == false)
		{
			ImGui::SetKeyboardFocusHere();
			storage->SetBool(id + 2, true);
		}

		ImGui::PushID("Edit");
		valueChanged = ImGui::InputFloat(label, v, 0.0f, 0.0f, format, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll);
		ImGui::PopID();

		if (ImGui::IsItemDeactivated() || (ImGui::IsItemHovered() == false && ImGui::IsMouseClicked(ImGuiMouseButton_Left)))
		{
			storage->SetBool(id, false);
			storage->SetBool(id + 2, false);
		}
	}
	else
	{
		valueChanged = ImGui::SliderScalar(label, ImGuiDataType_Float, v, &v_min, &v_max, format, flags);

		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::Selectable("Manual Edit"))
			{
				storage->SetBool(id, true);
			}
			ImGui::EndPopup();
		}
	}

	return valueChanged;
}

bool ImGui::SliderDoubleEditable(const char* label, double* v, double v_min, double v_max, const char* format, ImGuiSliderFlags flags)
{
	ImGuiID id = ImGui::GetID(label);
	ImGuiStorage* storage = ImGui::GetStateStorage();

	bool isEditing = storage->GetBool(id, false);
	bool valueChanged = false;

	if (isEditing)
	{
		bool wasFocused = storage->GetBool(id + 2, false);
		if (wasFocused == false)
		{
			ImGui::SetKeyboardFocusHere();
			storage->SetBool(id + 2, true);
		}

		ImGui::PushID("Edit");
		valueChanged = ImGui::InputDouble(label, v, 0.0, 0.0, format, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll);
		ImGui::PopID();

		if (ImGui::IsItemDeactivated() || (ImGui::IsItemHovered() == false && ImGui::IsMouseClicked(ImGuiMouseButton_Left)))
		{
			storage->SetBool(id, false);
			storage->SetBool(id + 2, false);
		}
	}
	else
	{
		valueChanged = ImGui::SliderScalar(label, ImGuiDataType_Double, v, &v_min, &v_max, format, flags);

		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::Selectable("Manual Edit"))
			{
				storage->SetBool(id, true);
			}
			ImGui::EndPopup();
		}
	}

	return valueChanged;
}




bool ImGui::ColorConfig3(const char* label, float color[3])
{
	bool valueChanged = false;

	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	ImGui::PushID(label);

	ImVec4 colorVector(color[0], color[1], color[2], 1.0f);
	ImVec2 buttonSize(40.0f, 0.0f);

	if (ImGui::ColorButton("##ColorButton", colorVector, ImGuiColorEditFlags_NoAlpha, buttonSize))
	{
		ImGui::OpenPopup("ColorPicker3Popup");
	}

	if (ImGui::BeginPopup("ColorPicker3Popup"))
	{
		if (ImGui::ColorPicker3("##picker", color, ImGuiColorEditFlags_NoLabel))
		{
			valueChanged = true;
		}
		ImGui::EndPopup();
	}

	ImGui::PopID();
	return valueChanged;
}

bool ImGui::ColorConfig4(const char* label, float color[4])
{
	bool valueChanged = false;

	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	ImGui::PushID(label);

	ImVec4 colorVector(color[0], color[1], color[2], color[3]);
	ImVec2 buttonSize(40.0f, 0.0f);

	if (ImGui::ColorButton("##ColorButton", colorVector, ImGuiColorEditFlags_AlphaPreview, buttonSize))
	{
		ImGui::OpenPopup("ColorPicker4Popup");
	}

	if (ImGui::BeginPopup("ColorPicker4Popup"))
	{
		if (ImGui::ColorPicker4("##picker", color, ImGuiColorEditFlags_NoLabel))
		{
			valueChanged = true;
		}
		ImGui::EndPopup();
	}

	ImGui::PopID();
	return valueChanged;
}




bool ImGui::ObjectFilterModeComboBox(const char* label, E_ObjectFilterMode* v)
{
	bool valueChanged = false;
	ImGui::PushID(label);

	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	static const char* items[] = { "Class Name", "Object Name", "All" };
	int index = static_cast<int>(*v);

	ImGui::SetNextItemWidth(200);
	if (ImGui::Combo("##object_filter_combo", &index, items, IM_ARRAYSIZE(items))) 
	{
		*v = static_cast<E_ObjectFilterMode>(index);
		valueChanged = true;
	}

	ImGui::PopID();
	return valueChanged;
}




int ImGui::ImGuiKey_ToWinAPI(const ImGuiKey& key)
{
	switch (key)
	{
		case ImGuiKey_Tab: return VK_TAB;
		case ImGuiKey_LeftArrow: return VK_LEFT;
		case ImGuiKey_RightArrow: return VK_RIGHT;
		case ImGuiKey_UpArrow: return VK_UP;
		case ImGuiKey_DownArrow: return VK_DOWN;
		case ImGuiKey_PageUp: return VK_PRIOR;
		case ImGuiKey_PageDown: return VK_NEXT;
		case ImGuiKey_Home: return VK_HOME;
		case ImGuiKey_End: return VK_END;
		case ImGuiKey_Insert: return VK_INSERT;
		case ImGuiKey_Delete: return VK_DELETE;
		case ImGuiKey_Backspace: return VK_BACK;
		case ImGuiKey_Space: return VK_SPACE;
		case ImGuiKey_Enter: return VK_RETURN;
		case ImGuiKey_Escape: return VK_ESCAPE;

		case ImGuiKey_PrintScreen: return VK_SNAPSHOT;
		case ImGuiKey_Pause: return VK_PAUSE;
		case ImGuiKey_CapsLock: return VK_CAPITAL;
		case ImGuiKey_ScrollLock: return VK_SCROLL;
		case ImGuiKey_NumLock: return VK_NUMLOCK;
		case ImGuiKey_Menu: return VK_APPS;

		case ImGuiKey_A: return 'A'; case ImGuiKey_B: return 'B';
		case ImGuiKey_C: return 'C'; case ImGuiKey_D: return 'D';
		case ImGuiKey_E: return 'E'; case ImGuiKey_F: return 'F';
		case ImGuiKey_G: return 'G'; case ImGuiKey_H: return 'H';
		case ImGuiKey_I: return 'I'; case ImGuiKey_J: return 'J';
		case ImGuiKey_K: return 'K'; case ImGuiKey_L: return 'L';
		case ImGuiKey_M: return 'M'; case ImGuiKey_N: return 'N';
		case ImGuiKey_O: return 'O'; case ImGuiKey_P: return 'P';
		case ImGuiKey_Q: return 'Q'; case ImGuiKey_R: return 'R';
		case ImGuiKey_S: return 'S'; case ImGuiKey_T: return 'T';
		case ImGuiKey_U: return 'U'; case ImGuiKey_V: return 'V';
		case ImGuiKey_W: return 'W'; case ImGuiKey_X: return 'X';
		case ImGuiKey_Y: return 'Y'; case ImGuiKey_Z: return 'Z';

		case ImGuiKey_0: return '0'; case ImGuiKey_1: return '1';
		case ImGuiKey_2: return '2'; case ImGuiKey_3: return '3';
		case ImGuiKey_4: return '4'; case ImGuiKey_5: return '5';
		case ImGuiKey_6: return '6'; case ImGuiKey_7: return '7';
		case ImGuiKey_8: return '8'; case ImGuiKey_9: return '9';

		case ImGuiKey_Minus: return VK_OEM_MINUS;
		case ImGuiKey_Equal: return VK_OEM_PLUS;
		case ImGuiKey_LeftBracket: return VK_OEM_4;
		case ImGuiKey_RightBracket: return VK_OEM_6;
		case ImGuiKey_Semicolon: return VK_OEM_1;
		case ImGuiKey_Apostrophe: return VK_OEM_7;
		case ImGuiKey_Comma: return VK_OEM_COMMA;
		case ImGuiKey_Period: return VK_OEM_PERIOD;
		case ImGuiKey_Slash: return VK_OEM_2;
		case ImGuiKey_Backslash: return VK_OEM_5;
		case ImGuiKey_GraveAccent: return VK_OEM_3;

		case ImGuiKey_Keypad0: return VK_NUMPAD0;
		case ImGuiKey_Keypad1: return VK_NUMPAD1;
		case ImGuiKey_Keypad2: return VK_NUMPAD2;
		case ImGuiKey_Keypad3: return VK_NUMPAD3;
		case ImGuiKey_Keypad4: return VK_NUMPAD4;
		case ImGuiKey_Keypad5: return VK_NUMPAD5;
		case ImGuiKey_Keypad6: return VK_NUMPAD6;
		case ImGuiKey_Keypad7: return VK_NUMPAD7;
		case ImGuiKey_Keypad8: return VK_NUMPAD8;
		case ImGuiKey_Keypad9: return VK_NUMPAD9;
		case ImGuiKey_KeypadMultiply: return VK_MULTIPLY;
		case ImGuiKey_KeypadAdd: return VK_ADD;
		case ImGuiKey_KeypadSubtract: return VK_SUBTRACT;
		case ImGuiKey_KeypadDecimal: return VK_DECIMAL;
		case ImGuiKey_KeypadDivide: return VK_DIVIDE;

		case ImGuiKey_F1: return VK_F1; case ImGuiKey_F2: return VK_F2;
		case ImGuiKey_F3: return VK_F3; case ImGuiKey_F4: return VK_F4;
		case ImGuiKey_F5: return VK_F5; case ImGuiKey_F6: return VK_F6;
		case ImGuiKey_F7: return VK_F7; case ImGuiKey_F8: return VK_F8;
		case ImGuiKey_F9: return VK_F9; case ImGuiKey_F10: return VK_F10;
		case ImGuiKey_F11: return VK_F11; case ImGuiKey_F12: return VK_F12;

		case ImGuiKey_LeftCtrl: return VK_LCONTROL;
		case ImGuiKey_RightCtrl: return VK_RCONTROL;
		case ImGuiKey_LeftShift: return VK_LSHIFT;
		case ImGuiKey_RightShift: return VK_RSHIFT;
		/* Left Alt recognition was disabled due to glitch with ALT + TABing. */
		// case ImGuiKey_LeftAlt: return VK_LMENU;
		case ImGuiKey_RightAlt: return VK_RMENU;
		case ImGuiKey_LeftSuper: return VK_LWIN;
		case ImGuiKey_RightSuper: return VK_RWIN;

		default: return 0;
	}
}

const char* ImGui::ImGuiKey_GetName(const ImGuiKey& key)
{
	switch (key)
	{
		case ImGuiKey_Tab:            return "Tab";
		case ImGuiKey_LeftArrow:      return "Left";
		case ImGuiKey_RightArrow:     return "Right";
		case ImGuiKey_UpArrow:        return "Up";
		case ImGuiKey_DownArrow:      return "Down";
		case ImGuiKey_PageUp:         return "PgUp";
		case ImGuiKey_PageDown:       return "PgDn";
		case ImGuiKey_Home:           return "Home";
		case ImGuiKey_End:            return "End";
		case ImGuiKey_Insert:         return "Ins";
		case ImGuiKey_Delete:         return "Del";
		case ImGuiKey_Backspace:      return "Bspace";
		case ImGuiKey_Space:          return "Space";
		case ImGuiKey_Enter:          return "Enter";
		case ImGuiKey_Escape:         return "Esc";

		case ImGuiKey_PrintScreen:    return "PrtSc";
		case ImGuiKey_Pause:          return "Pause";
		case ImGuiKey_CapsLock:       return "Caps";
		case ImGuiKey_ScrollLock:     return "ScrLk";
		case ImGuiKey_NumLock:        return "NumLk";
		case ImGuiKey_Menu:           return "Menu";

		case ImGuiKey_A: return "A";  case ImGuiKey_B: return "B";
		case ImGuiKey_C: return "C";  case ImGuiKey_D: return "D";
		case ImGuiKey_E: return "E";  case ImGuiKey_F: return "F";
		case ImGuiKey_G: return "G";  case ImGuiKey_H: return "H";
		case ImGuiKey_I: return "I";  case ImGuiKey_J: return "J";
		case ImGuiKey_K: return "K";  case ImGuiKey_L: return "L";
		case ImGuiKey_M: return "M";  case ImGuiKey_N: return "N";
		case ImGuiKey_O: return "O";  case ImGuiKey_P: return "P";
		case ImGuiKey_Q: return "Q";  case ImGuiKey_R: return "R";
		case ImGuiKey_S: return "S";  case ImGuiKey_T: return "T";
		case ImGuiKey_U: return "U";  case ImGuiKey_V: return "V";
		case ImGuiKey_W: return "W";  case ImGuiKey_X: return "X";
		case ImGuiKey_Y: return "Y";  case ImGuiKey_Z: return "Z";

		case ImGuiKey_0: return "0";  case ImGuiKey_1: return "1";
		case ImGuiKey_2: return "2";  case ImGuiKey_3: return "3";
		case ImGuiKey_4: return "4";  case ImGuiKey_5: return "5";
		case ImGuiKey_6: return "6";  case ImGuiKey_7: return "7";
		case ImGuiKey_8: return "8";  case ImGuiKey_9: return "9";

		case ImGuiKey_Minus:          return "-";
		case ImGuiKey_Equal:          return "=";
		case ImGuiKey_LeftBracket:    return "[";
		case ImGuiKey_RightBracket:   return "]";
		case ImGuiKey_Semicolon:      return ";";
		case ImGuiKey_Apostrophe:     return "'";
		case ImGuiKey_Comma:          return ",";
		case ImGuiKey_Period:         return ".";
		case ImGuiKey_Slash:          return "/";
		case ImGuiKey_Backslash:      return "\\";
		case ImGuiKey_GraveAccent:    return "`";

		case ImGuiKey_Keypad0:        return "Num0";
		case ImGuiKey_Keypad1:        return "Num1";
		case ImGuiKey_Keypad2:        return "Num2";
		case ImGuiKey_Keypad3:        return "Num3";
		case ImGuiKey_Keypad4:        return "Num4";
		case ImGuiKey_Keypad5:        return "Num5";
		case ImGuiKey_Keypad6:        return "Num6";
		case ImGuiKey_Keypad7:        return "Num7";
		case ImGuiKey_Keypad8:        return "Num8";
		case ImGuiKey_Keypad9:        return "Num9";
		case ImGuiKey_KeypadMultiply: return "Num*";
		case ImGuiKey_KeypadAdd:      return "Num+";
		case ImGuiKey_KeypadSubtract: return "Num-";
		case ImGuiKey_KeypadDecimal:  return "Num.";
		case ImGuiKey_KeypadDivide:   return "Num/";

		case ImGuiKey_F1:  return "F1";   case ImGuiKey_F2:  return "F2";
		case ImGuiKey_F3:  return "F3";   case ImGuiKey_F4:  return "F4";
		case ImGuiKey_F5:  return "F5";   case ImGuiKey_F6:  return "F6";
		case ImGuiKey_F7:  return "F7";   case ImGuiKey_F8:  return "F8";
		case ImGuiKey_F9:  return "F9";   case ImGuiKey_F10: return "F10";
		case ImGuiKey_F11: return "F11";  case ImGuiKey_F12: return "F12";

		case ImGuiKey_LeftCtrl:   return "LCtrl";
		case ImGuiKey_RightCtrl:  return "RCtrl";
		case ImGuiKey_LeftShift:  return "LShift";
		case ImGuiKey_RightShift: return "RShift";
		case ImGuiKey_LeftAlt:    return "LAlt";
		case ImGuiKey_RightAlt:   return "RAlt";
		case ImGuiKey_LeftSuper:  return "LWin";
		case ImGuiKey_RightSuper: return "RWin";

		default: return "???";
	}
}




bool ImGui::KeyBindingInput(const char* label, KeyBinding* binding)
{
	if (!binding)
		return false;

	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	ImGui::PushID(label ? label : "KeyBindingInput");

	SameLine();

	/* 0 corresponds for default vertical size. */
	static const ImVec2 buttonSize = { 96.0f, 0.0f };

	static const ImVec4 buttonColor = { 0.20f, 0.50f, 0.20f, 1.00f };
	static const ImVec4 buttonColor_unbound = { 0.50f, 0.20f, 0.20f, 1.00f };
	static const ImVec4 buttonColor_capturing = { 0.25f, 0.25f, 0.25f, 1.00f };

	bool hasBindingChanged = false;
	if (binding->isDetermined)
	{
		const char* bindingName;

		if (binding->key == ImGuiKey_None)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, buttonColor_unbound);
			bindingName = "?";
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
			bindingName = ImGuiKey_GetName(binding->key);
		}

		if (Button(bindingName, buttonSize))
			binding->isDetermined = false;
	}
	else
	{
		ImGui::PushStyleColor(ImGuiCol_Button, buttonColor_capturing);

		Button("...", buttonSize);
		for (int keyCode = ImGuiKey_NamedKey_BEGIN; keyCode < ImGuiKey_NamedKey_END; keyCode++)
		{
			if (IsKeyPressed((ImGuiKey)keyCode))
			{
				/* Verify that keyCode is within pre-determined list of keys. */
				if (ImGuiKey_ToWinAPI((ImGuiKey)keyCode) == 0)
					continue;

				/* When user tries to assign same key that is already set, consider that as will to unbind. */
				if (keyCode == binding->key)
					binding->key = ImGuiKey_None;
				else
					binding->key = (ImGuiKey)keyCode;

				binding->isDetermined = true;
				hasBindingChanged = true;

				Inputs::Config::Save();

				break;
			}
		}
	}

	ImGui::PopStyleColor();
	ImGui::PopID();

	return hasBindingChanged;
}

bool ImGui::IsKeyBindingPressed(KeyBinding* binding, bool waitForRelease)
{
	if (!binding)
		return false;

	if (binding->isDetermined == false)
		return false;

	if (binding->isInUse)
		return false;

	if (binding->key == ImGuiKey_None)
		return false;

	int keyCode = ImGuiKey_ToWinAPI(binding->key);
	if (waitForRelease)
	{
		if (GetAsyncKeyState(keyCode) & 0x8000)
		{
			binding->isInUse = true;
			while (GetAsyncKeyState(keyCode) & 0x8000)
			{
				Sleep(1);
			}

			binding->isInUse = false;
			return true;
		}
	}
	else
		return (GetAsyncKeyState(keyCode) & 1);

	return false;
}

bool ImGui::IsKeyBindingDown(KeyBinding* binding)
{
	if (!binding)
		return false;

	if (binding->isDetermined == false)
		return false;

	if (binding->isInUse)
		return true; // <-- !

	if (binding->key == ImGuiKey_None)
		return false;

	int keyCode = ImGuiKey_ToWinAPI(binding->key);
	if (GetAsyncKeyState(keyCode) & 0x8000)
		return true;

	return false;
}

bool ImGui::IsKeyBindingReleased(KeyBinding* binding)
{
	if (!binding)
		return false;

	if (binding->isDetermined == false)
		return false;

	if (binding->isInUse)
		return false;

	if (binding->key == ImGuiKey_None)
		return false;

	int keyCode = ImGuiKey_ToWinAPI(binding->key);
	return (GetAsyncKeyState(keyCode) & 0x8000) == false;
}




bool ImGui::IsMouseButtonDown(const E_MouseButton& mouseButton)
{
	int32_t virtualKey = 0;
	switch (mouseButton)
	{
		case E_MouseButton::Left:
			virtualKey = VK_LBUTTON;
			break;
		case E_MouseButton::Middle:
			virtualKey = VK_MBUTTON;
			break;
		case E_MouseButton::Right:
			virtualKey = VK_RBUTTON;
			break;
		default:
			return false;
	}

	return (GetAsyncKeyState(virtualKey) & 0x8000) != 0;
}




void ImGui::SetFontScale(float fontScale)
{
	SetWindowFontScale(fontScale);
	fontScale = E_FontScale::Custom;
}

void ImGui::SetFontScale(E_FontScale fontScale)
{
	switch (fontScale)
	{
		case E_FontScale::Tiny:
			SetFontTiny();
			break;

		case E_FontScale::Little:
			SetFontLittle();
			break;

		case E_FontScale::Small:
			SetFontSmall();
			break;

		case E_FontScale::Regular:
			SetFontRegular();
			break;

		case E_FontScale::Big:
			SetFontBig();
			break;

		case E_FontScale::Large:
			SetFontLarge();
			break;

		case E_FontScale::Title:
			SetFontTitle();
			break;

		default:
			SetFontRegular();
			break;
	}
}


void ImGui::SetFontTiny()
{
	SetWindowFontScale(0.5f);
	fontScale = E_FontScale::Tiny;
}

void ImGui::SetFontLittle()
{
	SetWindowFontScale(0.75f);
	fontScale = E_FontScale::Little;
}

void ImGui::SetFontSmall()
{
	SetWindowFontScale(0.9f);
	fontScale = E_FontScale::Small;
}

void ImGui::SetFontRegular()
{
	SetWindowFontScale(1.0f);
	fontScale = E_FontScale::Regular;
}

void ImGui::SetFontBig()
{
	SetWindowFontScale(1.1f);
	fontScale = E_FontScale::Big;
}

void ImGui::SetFontLarge()
{
	SetWindowFontScale(1.25f);
	fontScale = E_FontScale::Large;
}

void ImGui::SetFontTitle()
{
	SetWindowFontScale(1.5f);
	fontScale = E_FontScale::Title;
}


void ImGui::TinyText(const char* fmt, ...)
{
	E_FontScale previousFontScale = fontScale;
	SetFontTiny();

	va_list args;
	va_start(args, fmt);

	ImGui::TextV(fmt, args);
	va_end(args);

	SetFontScale(previousFontScale);
}

void ImGui::LittleText(const char* fmt, ...)
{
	E_FontScale previousFontScale = fontScale;
	SetFontLittle();

	va_list args;
	va_start(args, fmt);

	ImGui::TextV(fmt, args);
	va_end(args);

	SetFontScale(previousFontScale);
}

void ImGui::SmallText(const char* fmt, ...)
{
	E_FontScale previousFontScale = fontScale;
	SetFontSmall();

	va_list args;
	va_start(args, fmt);

	ImGui::TextV(fmt, args);
	va_end(args);

	SetFontScale(previousFontScale);
}

void ImGui::BigText(const char* fmt, ...)
{
	E_FontScale previousFontScale = fontScale;
	SetFontBig();

	va_list args;
	va_start(args, fmt);

	ImGui::TextV(fmt, args);
	va_end(args);

	SetFontScale(previousFontScale);
}

void ImGui::LargeText(const char* fmt, ...)
{
	E_FontScale previousFontScale = fontScale;
	SetFontLarge();

	va_list args;
	va_start(args, fmt);

	ImGui::TextV(fmt, args);
	va_end(args);

	SetFontScale(previousFontScale);
}

void ImGui::TitleText(const char* fmt, ...)
{
	E_FontScale previousFontScale = fontScale;
	SetFontTitle();

	va_list args;
	va_start(args, fmt);

	ImGui::TextV(fmt, args);
	va_end(args);

	SetFontScale(previousFontScale);
}






// ==============================
// |            #GUI			|
// ==============================
bool GUI::StartWindowThread()
{
	if (windowThread)
		return false;

#if defined(API_D3D11)
	windowThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DirectWindow11::Create, 0, 0, 0);
#elif defined(API_OPENGL3)
	windowThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)OpenWindow3::Create, 0, 0, 0);
#endif

	return windowThread;
}




void GUI::Init(const HMODULE& applicationModule)
{
	/* Before creating a DirectWindow, we need to make it aware of our DLL HMODULE. */
#if defined(API_D3D11)
	DirectWindow11::SetApplicationModule(applicationModule);
#elif defined(API_OPENGL3)
	OpenWindow3::SetApplicationModule(applicationModule);
#endif
	StartWindowThread();

	Features::Config::Load();
	Features::Positions::Load();
	Inputs::Config::Load();

	BackgroundTasks::Init();
}

#ifdef WAIT_FOR_TITLE_INIT
void GUI::InitOnTitleInitialized(const HMODULE& applicationModule)
{
	while (Unreal::IsTitleInitialized() == false)
		Sleep(100);

	Init(applicationModule);
}
#endif




void GUI::Draw()
{
	if (GetIsMenuActive())
	{
		if (ImGui::BeginMainMenuBar())
		{
			ImGui::Text("UETools GUI (v%s)", APP_VERSION_STRING_SHORT);
			if (ImGui::IsItemHovered())
			{
				ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
			}
			if (ImGui::IsItemClicked())
			{
				ShellExecuteA(NULL, "open", "https://github.com/Cranch-fur/UETools-GUI", NULL, NULL, SW_SHOWNORMAL);
			}
#ifdef _DEBUG
			if (GetIsMenuDebugEnabled())
				ImGui::Text("[%d]", GetMenuDebugLevel());
			else 
				ImGui::Text("[D]");

			if (ImGui::IsItemHovered())
			{
				ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
			}
			if (ImGui::IsItemClicked())
			{
				SwitchMenuDebugLevel();
			}

			if (GetIsMenuDebugEnabled())
			{
				ImGui::ShowDemoWindow();

				if (GetIsMenuDebugDetailed())
				{
					ImGui::ShowDebugLogWindow();
					ImGui::ShowIDStackToolWindow();
				}
			}

			ImGui::Text(" | ");
			ImGui::Text("%.1f FPS (%.3f ms)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
			if (ImGui::IsItemHovered())
			{
				ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
				ImGui::BeginTooltip();
				ImGui::Text("%d visible windows", ImGui::GetIO().MetricsRenderWindows);
				ImGui::Text("%d vertices, %d indices (%d triangles)", ImGui::GetIO().MetricsRenderVertices, ImGui::GetIO().MetricsRenderIndices, ImGui::GetIO().MetricsRenderIndices / 3);
				ImGui::EndTooltip();
			}
#endif

			ImGui::Text(" | ");

			Templates::Menus::Debug::Draw();

			Templates::Menus::World::Draw();

			Templates::Menus::Character::Draw();

			Templates::Menus::FreeCamera::Draw();

			Templates::Menus::Settings::Draw();

			ImGui::Text(" | ");

			Templates::Menus::BootlegConsole::Draw();


			ImGui::EndMainMenuBar();
		}
	}

	Features::ActorTrace::Draw_ThreadSafe();

	if (Features::ActorsTracker::enabled)
		Features::ActorsTracker::Draw_ThreadSafe();

#ifdef COLLISION_VISUALIZER
	if (Features::CollisionVisualizer::enabled)
		Features::CollisionVisualizer::Draw_ThreadSafe();
#endif

	Features::WidgetVisualisation::Draw_ThreadSafe();
}




void GUI::PlayUISound(const E_Sound& soundToPlay)
{
	if (Features::Menu::enableSound == false)
		return;

	uint16_t soundFrequency;
	uint16_t soundDuration;

	switch (soundToPlay)
	{
		case E_Sound::BUTTON_PRESS:
			soundFrequency = 245;
			soundDuration = 50;
			break;

		case E_Sound::BUTTON_CANCEL:
			soundFrequency = 100;
			soundDuration = 150;
			break;

		case E_Sound::ACTION_SUCCESS:
			soundFrequency = 350;
			soundDuration = 300;
			break;

		case E_Sound::ACTION_ERROR:
			soundFrequency = 175;
			soundDuration = 300;
			break;

		default:
			soundFrequency = 500;
			soundDuration = 1000;
			break;
	}

	/*
		Dedicate sound playback in to separate thread.
		This prevents the main thread from blocking while Beep() is playing the sound.
	*/
	std::thread([=]()
		{
			Beep(soundFrequency, soundDuration);
		}).detach();
}






// ==============================
// |        #Features			|
// ==============================
template <typename T>
inline void Features::Config::ReadFeatureFromConfig(ConfigInstance* featuresConfig, const std::string& entryName, T* featureValue)
{
	if (featuresConfig == nullptr || featureValue == nullptr)
		return;

	if (featuresConfig->HasKey(entryName) == false)
		return;

	*featureValue = featuresConfig->GetKey<T>(entryName).value_or(*featureValue);
}

void Features::Config::Load()
{
	ConfigInstance featuresConfig(PATH_CONFIG_FEATURES);
	if (featuresConfig.Load() == false)
	{
		Features::Config::Save();
		featuresConfig.Load();
	}

	ReadFeatureFromConfig(&featuresConfig, "Features_Menu_enableSound", &Features::Menu::enableSound);
	ReadFeatureFromConfig(&featuresConfig, "Features_Menu_useVectorFont", &Features::Menu::useVectorFont);

	ReadFeatureFromConfig(&featuresConfig, "Features_Debug_autoUpdate", &Features::Debug::autoUpdate);
	ReadFeatureFromConfig(&featuresConfig, "Features_Debug_autoUpdateDelay", &Features::Debug::autoUpdateDelay);

	ReadFeatureFromConfig(&featuresConfig, "Features_DirectionalMovement_enabled", &Features::DirectionalMovement::enabled);
	ReadFeatureFromConfig(&featuresConfig, "Features_DirectionalMovement_omniMovement", &Features::DirectionalMovement::omniMovement);
	ReadFeatureFromConfig(&featuresConfig, "Features_DirectionalMovement_independentOmniMovement", &Features::DirectionalMovement::independentOmniMovement);
	ReadFeatureFromConfig(&featuresConfig, "Features_DirectionalMovement_step", &Features::DirectionalMovement::step);
	ReadFeatureFromConfig(&featuresConfig, "Features_DirectionalMovement_delay", &Features::DirectionalMovement::delay);

	std::array<float, 4> widgetVisualisationColor = { Features::WidgetVisualisation::color[0], Features::WidgetVisualisation::color[1],
													  Features::WidgetVisualisation::color[2], Features::WidgetVisualisation::color[3] };
	ReadFeatureFromConfig(&featuresConfig, "Features_WidgetVisualisation_color", &widgetVisualisationColor);
	Features::WidgetVisualisation::color[0] = widgetVisualisationColor[0];
	Features::WidgetVisualisation::color[1] = widgetVisualisationColor[1];
	Features::WidgetVisualisation::color[2] = widgetVisualisationColor[2];
	Features::WidgetVisualisation::color[3] = widgetVisualisationColor[3];

	ReadFeatureFromConfig(&featuresConfig, "Features_WidgetVisualisation_lineThickness", &Features::WidgetVisualisation::lineThickness);

	ReadFeatureFromConfig(&featuresConfig, "Features_ActorTrace_showOnScreen", &Features::ActorTrace::showOnScreen);

	std::array<float, 4> actorTraceColor = { Features::ActorTrace::traceColor[0], Features::ActorTrace::traceColor[1],
											 Features::ActorTrace::traceColor[2], Features::ActorTrace::traceColor[3] };
	ReadFeatureFromConfig(&featuresConfig, "Features_ActorTrace_traceColor", &actorTraceColor);
	Features::ActorTrace::traceColor[0] = actorTraceColor[0];
	Features::ActorTrace::traceColor[1] = actorTraceColor[1];
	Features::ActorTrace::traceColor[2] = actorTraceColor[2];
	Features::ActorTrace::traceColor[3] = actorTraceColor[3];

	ReadFeatureFromConfig(&featuresConfig, "Features_ActorTrace_traceThickness", &Features::ActorTrace::traceThickness);
	ReadFeatureFromConfig(&featuresConfig, "Features_ActorTrace_traceDistance", &Features::ActorTrace::traceDistance);

#ifdef COLLISION_VISUALIZER
	std::array<float, 4> color_StaticMesh = { Features::CollisionVisualizer::color_StaticMesh[0], Features::CollisionVisualizer::color_StaticMesh[1],
											  Features::CollisionVisualizer::color_StaticMesh[2], Features::CollisionVisualizer::color_StaticMesh[3]};
	ReadFeatureFromConfig(&featuresConfig, "Features_CollisionVisualizer_color_StaticMesh", &color_StaticMesh);
	Features::CollisionVisualizer::color_StaticMesh[0] = color_StaticMesh[0];
	Features::CollisionVisualizer::color_StaticMesh[1] = color_StaticMesh[1];
	Features::CollisionVisualizer::color_StaticMesh[2] = color_StaticMesh[2];
	Features::CollisionVisualizer::color_StaticMesh[3] = color_StaticMesh[3];


	std::array<float, 4> color_Primitive = { Features::CollisionVisualizer::color_Primitive[0], Features::CollisionVisualizer::color_Primitive[1],
											 Features::CollisionVisualizer::color_Primitive[2], Features::CollisionVisualizer::color_Primitive[3] };
	ReadFeatureFromConfig(&featuresConfig, "Features_CollisionVisualizer_color_Primitive", &color_Primitive);
	Features::CollisionVisualizer::color_Primitive[0] = color_Primitive[0];
	Features::CollisionVisualizer::color_Primitive[1] = color_Primitive[1];
	Features::CollisionVisualizer::color_Primitive[2] = color_Primitive[2];
	Features::CollisionVisualizer::color_Primitive[3] = color_Primitive[3];


	std::array<float, 4> color_PhysicsVolume = { Features::CollisionVisualizer::color_PhysicsVolume[0], Features::CollisionVisualizer::color_PhysicsVolume[1],
												 Features::CollisionVisualizer::color_PhysicsVolume[2], Features::CollisionVisualizer::color_PhysicsVolume[3] };
	ReadFeatureFromConfig(&featuresConfig, "Features_CollisionVisualizer_color_PhysicsVolume", &color_PhysicsVolume);
	Features::CollisionVisualizer::color_PhysicsVolume[0] = color_PhysicsVolume[0];
	Features::CollisionVisualizer::color_PhysicsVolume[1] = color_PhysicsVolume[1];
	Features::CollisionVisualizer::color_PhysicsVolume[2] = color_PhysicsVolume[2];
	Features::CollisionVisualizer::color_PhysicsVolume[3] = color_PhysicsVolume[3];


	std::array<float, 4> color_BlockingVolume = { Features::CollisionVisualizer::color_BlockingVolume[0], Features::CollisionVisualizer::color_BlockingVolume[1],
												  Features::CollisionVisualizer::color_BlockingVolume[2], Features::CollisionVisualizer::color_BlockingVolume[3] };
	ReadFeatureFromConfig(&featuresConfig, "Features_CollisionVisualizer_color_BlockingVolume", &color_BlockingVolume);
	Features::CollisionVisualizer::color_BlockingVolume[0] = color_BlockingVolume[0];
	Features::CollisionVisualizer::color_BlockingVolume[1] = color_BlockingVolume[1];
	Features::CollisionVisualizer::color_BlockingVolume[2] = color_BlockingVolume[2];
	Features::CollisionVisualizer::color_BlockingVolume[3] = color_BlockingVolume[3];


	std::array<float, 4> color_TriggerVolume = { Features::CollisionVisualizer::color_TriggerVolume[0], Features::CollisionVisualizer::color_TriggerVolume[1],
												 Features::CollisionVisualizer::color_TriggerVolume[2], Features::CollisionVisualizer::color_TriggerVolume[3] };
	ReadFeatureFromConfig(&featuresConfig, "Features_CollisionVisualizer_color_TriggerVolume", &color_TriggerVolume);
	Features::CollisionVisualizer::color_TriggerVolume[0] = color_TriggerVolume[0];
	Features::CollisionVisualizer::color_TriggerVolume[1] = color_TriggerVolume[1];
	Features::CollisionVisualizer::color_TriggerVolume[2] = color_TriggerVolume[2];
	Features::CollisionVisualizer::color_TriggerVolume[3] = color_TriggerVolume[3];


	std::array<float, 4> color_PostProcessVolume = { Features::CollisionVisualizer::color_PostProcessVolume[0], Features::CollisionVisualizer::color_PostProcessVolume[1],
													 Features::CollisionVisualizer::color_PostProcessVolume[2], Features::CollisionVisualizer::color_PostProcessVolume[3] };
	ReadFeatureFromConfig(&featuresConfig, "Features_CollisionVisualizer_color_PostProcessVolume", &color_PostProcessVolume);
	Features::CollisionVisualizer::color_PostProcessVolume[0] = color_PostProcessVolume[0];
	Features::CollisionVisualizer::color_PostProcessVolume[1] = color_PostProcessVolume[1];
	Features::CollisionVisualizer::color_PostProcessVolume[2] = color_PostProcessVolume[2];
	Features::CollisionVisualizer::color_PostProcessVolume[3] = color_PostProcessVolume[3];


	std::array<float, 4> color_Other = { Features::CollisionVisualizer::color_Other[0], Features::CollisionVisualizer::color_Other[1],
										 Features::CollisionVisualizer::color_Other[2], Features::CollisionVisualizer::color_Other[3] };
	ReadFeatureFromConfig(&featuresConfig, "Features_CollisionVisualizer_color_Other", &color_Other);
	Features::CollisionVisualizer::color_Other[0] = color_Other[0];
	Features::CollisionVisualizer::color_Other[1] = color_Other[1];
	Features::CollisionVisualizer::color_Other[2] = color_Other[2];
	Features::CollisionVisualizer::color_Other[3] = color_Other[3];


	ReadFeatureFromConfig(&featuresConfig, "Features_CollisionVisualizer_thickness", &Features::CollisionVisualizer::thickness);
#endif

	std::array<float, 4> actorColor = { Features::ActorsTracker::actorColor[0], Features::ActorsTracker::actorColor[1],
										Features::ActorsTracker::actorColor[2], Features::ActorsTracker::actorColor[3] };
	ReadFeatureFromConfig(&featuresConfig, "Features_ActorsTracker_actorColor", &actorColor);
	Features::ActorsTracker::actorColor[0] = actorColor[0];
	Features::ActorsTracker::actorColor[1] = actorColor[1];
	Features::ActorsTracker::actorColor[2] = actorColor[2];
	Features::ActorsTracker::actorColor[3] = actorColor[3];

	ReadFeatureFromConfig(&featuresConfig, "Features_ActorsTracker_showDistance", &Features::ActorsTracker::showDistance);
	ReadFeatureFromConfig(&featuresConfig, "Features_ActorsTracker_fadeOnCloseup", &Features::ActorsTracker::fadeOnCloseup);

	ReadFeatureFromConfig(&featuresConfig, "Features_FreeCamera_forceFreezePlayer", &Features::FreeCamera::forceFreezePlayer);

	ReadFeatureFromConfig(&featuresConfig, "Features_FreeCamera_forceDisablePlayerInput", &Features::FreeCamera::forceDisablePlayerInput);

	ReadFeatureFromConfig(&featuresConfig, "Features_FreeCamera_cameraMovementStep", &Features::FreeCamera::cameraMovementStep);
	ReadFeatureFromConfig(&featuresConfig, "Features_FreeCamera_cameraRotationStep", &Features::FreeCamera::cameraRotationStep);

	ReadFeatureFromConfig(&featuresConfig, "Features_FreeCamera_useMouseControl", &Features::FreeCamera::useMouseControl);
	ReadFeatureFromConfig(&featuresConfig, "Features_FreeCamera_mouseControlOnHold", &Features::FreeCamera::mouseControlOnHold);
	ReadFeatureFromConfig(&featuresConfig, "Features_FreeCamera_mouseControlXInverted", &Features::FreeCamera::mouseControlXInverted);
	ReadFeatureFromConfig(&featuresConfig, "Features_FreeCamera_mouseControlYInverted", &Features::FreeCamera::mouseControlYInverted);
	ReadFeatureFromConfig(&featuresConfig, "Features_FreeCamera_mouseControlSensitivity", &Features::FreeCamera::mouseControlSensitivity);
	ReadFeatureFromConfig(&featuresConfig, "Features_FreeCamera_mouseControlLimitMaximumDelta", &Features::FreeCamera::mouseControlLimitMaximumDelta);
	ReadFeatureFromConfig(&featuresConfig, "Features_FreeCamera_mouseControlMaximumDelta", &Features::FreeCamera::mouseControlMaximumDelta);
}

void Features::Config::Save()
{
	ConfigInstance featuresConfig(PATH_CONFIG_FEATURES);

	featuresConfig.SetKey("Features_Menu_enableSound", Features::Menu::enableSound);
	featuresConfig.SetKey("Features_Menu_useVectorFont", Features::Menu::useVectorFont);

	featuresConfig.SetKey("Features_Debug_autoUpdate", Features::Debug::autoUpdate);
	featuresConfig.SetKey("Features_Debug_autoUpdateDelay", Features::Debug::autoUpdateDelay);

	featuresConfig.SetKey("Features_DirectionalMovement_enabled", Features::DirectionalMovement::enabled);
	featuresConfig.SetKey("Features_DirectionalMovement_omniMovement", Features::DirectionalMovement::omniMovement);
	featuresConfig.SetKey("Features_DirectionalMovement_independentOmniMovement", Features::DirectionalMovement::independentOmniMovement);
	featuresConfig.SetKey("Features_DirectionalMovement_step", Features::DirectionalMovement::step);
	featuresConfig.SetKey("Features_DirectionalMovement_delay", Features::DirectionalMovement::delay);

	std::array<float, 4> widgetVisualisationColor = { Features::WidgetVisualisation::color[0], Features::WidgetVisualisation::color[1],
													  Features::WidgetVisualisation::color[2], Features::WidgetVisualisation::color[3] };
	featuresConfig.SetKey("Features_WidgetVisualisation_color", widgetVisualisationColor);

	featuresConfig.SetKey("Features_WidgetVisualisation_lineThickness", Features::WidgetVisualisation::lineThickness);

	featuresConfig.SetKey("Features_ActorTrace_showOnScreen", Features::ActorTrace::showOnScreen);

	std::array<float, 4> actorTraceColor = { Features::ActorTrace::traceColor[0], Features::ActorTrace::traceColor[1],
											 Features::ActorTrace::traceColor[2], Features::ActorTrace::traceColor[3] };
	featuresConfig.SetKey("Features_ActorTrace_traceColor", actorTraceColor);

	featuresConfig.SetKey("Features_ActorTrace_traceThickness", Features::ActorTrace::traceThickness);
	featuresConfig.SetKey("Features_ActorTrace_traceDistance", Features::ActorTrace::traceDistance);

#ifdef COLLISION_VISUALIZER
	std::array<float, 4> color_StaticMesh = { Features::CollisionVisualizer::color_StaticMesh[0], Features::CollisionVisualizer::color_StaticMesh[1],
											  Features::CollisionVisualizer::color_StaticMesh[2], Features::CollisionVisualizer::color_StaticMesh[3] };
	featuresConfig.SetKey("Features_CollisionVisualizer_color_StaticMesh", color_StaticMesh);


	std::array<float, 4> color_Primitive = { Features::CollisionVisualizer::color_Primitive[0], Features::CollisionVisualizer::color_Primitive[1],
											 Features::CollisionVisualizer::color_Primitive[2], Features::CollisionVisualizer::color_Primitive[3] };
	featuresConfig.SetKey("Features_CollisionVisualizer_color_Primitive", color_Primitive);


	std::array<float, 4> color_PhysicsVolume = { Features::CollisionVisualizer::color_PhysicsVolume[0], Features::CollisionVisualizer::color_PhysicsVolume[1],
												 Features::CollisionVisualizer::color_PhysicsVolume[2], Features::CollisionVisualizer::color_PhysicsVolume[3] };
	featuresConfig.SetKey("Features_CollisionVisualizer_color_PhysicsVolume", color_PhysicsVolume);


	std::array<float, 4> color_BlockingVolume = { Features::CollisionVisualizer::color_BlockingVolume[0], Features::CollisionVisualizer::color_BlockingVolume[1],
												  Features::CollisionVisualizer::color_BlockingVolume[2], Features::CollisionVisualizer::color_BlockingVolume[3] };
	featuresConfig.SetKey("Features_CollisionVisualizer_color_BlockingVolume", color_BlockingVolume);


	std::array<float, 4> color_TriggerVolume = { Features::CollisionVisualizer::color_TriggerVolume[0], Features::CollisionVisualizer::color_TriggerVolume[1],
												 Features::CollisionVisualizer::color_TriggerVolume[2], Features::CollisionVisualizer::color_TriggerVolume[3] };
	featuresConfig.SetKey("Features_CollisionVisualizer_color_TriggerVolume", color_TriggerVolume);


	std::array<float, 4> color_PostProcessVolume = { Features::CollisionVisualizer::color_PostProcessVolume[0], Features::CollisionVisualizer::color_PostProcessVolume[1],
													 Features::CollisionVisualizer::color_PostProcessVolume[2], Features::CollisionVisualizer::color_PostProcessVolume[3] };
	featuresConfig.SetKey("Features_CollisionVisualizer_color_PostProcessVolume", color_PostProcessVolume);


	std::array<float, 4> color_Other = { Features::CollisionVisualizer::color_Other[0], Features::CollisionVisualizer::color_Other[1],
										 Features::CollisionVisualizer::color_Other[2], Features::CollisionVisualizer::color_Other[3] };
	featuresConfig.SetKey("Features_CollisionVisualizer_color_Other", color_Other);


	featuresConfig.SetKey("Features_CollisionVisualizer_thickness", Features::CollisionVisualizer::thickness);
#endif

	std::array<float, 4> actorColor = { Features::ActorsTracker::actorColor[0], Features::ActorsTracker::actorColor[1],
										Features::ActorsTracker::actorColor[2], Features::ActorsTracker::actorColor[3] };
	featuresConfig.SetKey("Features_ActorsTracker_actorColor", actorColor);

	featuresConfig.SetKey("Features_ActorsTracker_showDistance", Features::ActorsTracker::showDistance);
	featuresConfig.SetKey("Features_ActorsTracker_checkValidness", Features::ActorsTracker::fadeOnCloseup);

	featuresConfig.SetKey("Features_FreeCamera_forceFreezePlayer", Features::FreeCamera::forceFreezePlayer);

	featuresConfig.SetKey("Features_FreeCamera_forceDisablePlayerInput", Features::FreeCamera::forceDisablePlayerInput);

	featuresConfig.SetKey("Features_FreeCamera_cameraMovementStep", Features::FreeCamera::cameraMovementStep);
	featuresConfig.SetKey("Features_FreeCamera_cameraRotationStep", Features::FreeCamera::cameraRotationStep);

	featuresConfig.SetKey("Features_FreeCamera_useMouseControl", Features::FreeCamera::useMouseControl);
	featuresConfig.SetKey("Features_FreeCamera_mouseControlOnHold", Features::FreeCamera::mouseControlOnHold);
	featuresConfig.SetKey("Features_FreeCamera_mouseControlXInverted", Features::FreeCamera::mouseControlXInverted);
	featuresConfig.SetKey("Features_FreeCamera_mouseControlYInverted", Features::FreeCamera::mouseControlYInverted);
	featuresConfig.SetKey("Features_FreeCamera_mouseControlSensitivity", Features::FreeCamera::mouseControlSensitivity);
	featuresConfig.SetKey("Features_FreeCamera_mouseControlLimitMaximumDelta", Features::FreeCamera::mouseControlLimitMaximumDelta);
	featuresConfig.SetKey("Features_FreeCamera_mouseControlMaximumDelta", Features::FreeCamera::mouseControlMaximumDelta);

	featuresConfig.Save();
}




void Features::Debug::Update()
{
	SDK::UEngine* engine = Unreal::Engine::Get();
	if (Features::Debug::engine.reference = engine)
	{
		Features::Debug::engine.className = engine->Class->GetFullName();
		Features::Debug::engine.objectName = engine->GetFullName();

		Features::Debug::engine.fixedFrameRateEnabled = engine->bUseFixedFrameRate;
		Features::Debug::engine.fixedFrameRate = engine->FixedFrameRate;

		Features::Debug::engine.smoothFrameRateEnabled = engine->bSmoothFrameRate;
		Features::Debug::engine.smoothFrameRateRange = engine->SmoothedFrameRateRange;

		Features::Debug::engine.subtitlesEnabled = engine->bSubtitlesEnabled;
		Features::Debug::engine.subtitlesForcedOff = engine->bSubtitlesForcedOff;

		Features::Debug::engine.pauseOnLossOfFocus = engine->bPauseOnLossOfFocus;

		SDK::UGameViewportClient* viewportClient = engine->GameViewport;
		if (Features::Debug::engine.gameViewportClient.reference = viewportClient)
		{
			Features::Debug::engine.gameViewportClient.className = viewportClient->Class->GetFullName();
			Features::Debug::engine.gameViewportClient.objectName = viewportClient->GetFullName();

			SDK::UConsole* console = viewportClient->ViewportConsole;
			if (Features::Debug::engine.gameViewportClient.console.reference = console)
			{
				Features::Debug::engine.gameViewportClient.console.className = console->Class->GetFullName();
				Features::Debug::engine.gameViewportClient.console.objectName = console->GetFullName();
			}
		}
	}


	SDK::UGameInstance* gameInstance = Unreal::GameInstance::Get();
	if (Features::Debug::gameInstance.reference = gameInstance)
	{
		Features::Debug::gameInstance.className = gameInstance->Class->GetFullName();
		Features::Debug::gameInstance.objectName = gameInstance->GetFullName();

		SDK::UOnlineSession* onlineSession = gameInstance->OnlineSession;
		if (Features::Debug::gameInstance.onlineSession.reference = onlineSession)
		{
			Features::Debug::gameInstance.onlineSession.className = gameInstance->Class->GetFullName();
			Features::Debug::gameInstance.onlineSession.objectName = gameInstance->GetFullName();
		}
	}


	SDK::AGameModeBase* gameMode = Unreal::GameMode::Get();
	if (Features::Debug::gameMode.reference = gameMode)
	{
		Features::Debug::gameMode.className = gameMode->Class->GetFullName();
		Features::Debug::gameMode.objectName = gameMode->GetFullName();

		SDK::AGameSession* gameSession = gameMode->GameSession;
		if (Features::Debug::gameMode.gameSession.reference = gameSession)
		{
			Features::Debug::gameMode.gameSession.className = gameSession->Class->GetFullName();
			Features::Debug::gameMode.gameSession.objectName = gameSession->GetFullName();

			Features::Debug::gameMode.gameSession.maxPlayers = gameSession->MaxPlayers;
			Features::Debug::gameMode.gameSession.maxSpectators = gameSession->MaxSpectators;
			Features::Debug::gameMode.gameSession.maxPartySize = gameSession->MaxPartySize;
			Features::Debug::gameMode.gameSession.maxSplitScreensPerConnection = gameSession->MaxSplitscreensPerConnection;

			Features::Debug::gameMode.gameSession.sessionName = gameSession->SessionName.ToString();
		}

		Features::Debug::gameMode.playersCount = gameMode->GetNumPlayers();
		Features::Debug::gameMode.spectatorsCount = gameMode->GetNumSpectators();

		Features::Debug::gameMode.startPlayersAsSpectators = gameMode->bStartPlayersAsSpectators;
		Features::Debug::gameMode.defaultPlayerName = gameMode->DefaultPlayerName.ToString();

		Features::Debug::gameMode.useSeamlessTravel = gameMode->bUseSeamlessTravel;
		Features::Debug::gameMode.options = gameMode->OptionsString.ToString();

		Features::Debug::gameMode.isPausable = gameMode->bPauseable;
	}


	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (Features::Debug::playerController.reference = playerController)
	{
		Features::Debug::playerController.className = playerController->Class->GetFullName();
		Features::Debug::playerController.objectName = playerController->GetFullName();


		SDK::UPlayer* player = playerController->Player;
		if (Features::Debug::playerController.player.reference = player)
		{
			Features::Debug::playerController.player.className = player->Class->GetFullName();
			Features::Debug::playerController.player.objectName = player->GetFullName();
		}


		SDK::APawn* pawn = playerController->AcknowledgedPawn;
		if (Features::Debug::playerController.pawn.reference = pawn)
		{
			Features::Debug::playerController.pawn.className = pawn->Class->GetFullName();
			Features::Debug::playerController.pawn.objectName = pawn->GetFullName();

			Features::Debug::playerController.pawn.transform = Unreal::Actor::GetTransform(pawn);

			Features::Debug::playerController.pawn.isControlled = pawn->IsControlled();
			/*
				IsPawnControlled() isn't present in older versions of the Engine (e.g. 4.22.3). Use following code:
				Features::Debug::playerController.pawn.isPawnControlled = false;
			*/
			Features::Debug::playerController.pawn.isPawnControlled = pawn->IsPawnControlled();
			Features::Debug::playerController.pawn.isPlayerControlled = pawn->IsPlayerControlled();
			Features::Debug::playerController.pawn.isLocallyControlled = pawn->IsLocallyControlled();
			Features::Debug::playerController.pawn.isBotControlled = pawn->IsBotControlled();
		}


		SDK::APlayerCameraManager* cameraManager = playerController->PlayerCameraManager;
		if (Features::Debug::playerController.cameraManager.reference = cameraManager)
		{
			Features::Debug::playerController.cameraManager.className = cameraManager->Class->GetFullName();
			Features::Debug::playerController.cameraManager.objectName = cameraManager->GetFullName();

			Features::Debug::playerController.cameraManager.transform = Unreal::Actor::GetTransform(cameraManager);
		}


		SDK::UCheatManager* cheatManager = playerController->CheatManager;
		if (Features::Debug::playerController.cheatManager.reference = cheatManager)
		{
			Features::Debug::playerController.cheatManager.className = cheatManager->Class->GetFullName();
			Features::Debug::playerController.cheatManager.objectName = cheatManager->GetFullName();
		}
	}


	SDK::UWorld* world = SDK::UWorld::GetWorld();
	if (Features::Debug::world.reference = world)
	{
		Features::Debug::world.className = world->Class->GetFullName();
		Features::Debug::world.objectName = world->GetFullName();

		if (SDK::AGameStateBase* gameState = world->GameState)
		{
			Features::Debug::world.gameState.reference = gameState;

			Features::Debug::world.gameState.className = gameState->Class->GetFullName();
			Features::Debug::world.gameState.objectName = gameState->GetFullName();
		}

		if (SDK::UNetDriver* netDriver = world->NetDriver)
		{
			Features::Debug::world.netDriver.reference = netDriver;

			Features::Debug::world.netDriver.className = netDriver->Class->GetFullName();
			Features::Debug::world.netDriver.objectName = netDriver->GetFullName();
		}

		if (SDK::UNetDriver* demoNetDriver = world->NetDriver)
		{
			Features::Debug::world.demoNetDriver.reference = demoNetDriver;

			Features::Debug::world.demoNetDriver.className = demoNetDriver->Class->GetFullName();
			Features::Debug::world.demoNetDriver.objectName = demoNetDriver->GetFullName();
		}

		if (SDK::ULevel* persistentLevel = world->PersistentLevel)
		{
			Features::Debug::world.persistentLevel.reference = persistentLevel;

			Features::Debug::world.persistentLevel.className = persistentLevel->Class->GetFullName();
			Features::Debug::world.persistentLevel.objectName = persistentLevel->GetFullName();

			Features::Debug::world.persistentLevel.isVisible = persistentLevel->bIsVisible;

			if (SDK::AWorldSettings* worldSettings = persistentLevel->WorldSettings)
			{
				Features::Debug::world.persistentLevel.worldSettings.reference = worldSettings;
				Features::Debug::world.persistentLevel.worldSettings.className = worldSettings->Class->GetFullName();
				Features::Debug::world.persistentLevel.worldSettings.objectName = worldSettings->GetFullName();

				Features::Debug::world.persistentLevel.worldSettings.highPriorityLoading = worldSettings->bHighPriorityLoading;
				Features::Debug::world.persistentLevel.worldSettings.localHighPriorityLoading = worldSettings->bHighPriorityLoadingLocal;

				Features::Debug::world.persistentLevel.worldSettings.unitsToMeters = worldSettings->WorldToMeters;
			}
		}

		Features::Debug::world.gameTimeInSeconds = SDK::UKismetSystemLibrary::GetGameTimeInSeconds(world);

		Features::Debug::world.isServer = SDK::UKismetSystemLibrary::IsServer(world);
		Features::Debug::world.isDedicatedServer = SDK::UKismetSystemLibrary::IsDedicatedServer(world);
		/*
			IsSplitScreen() isn't present in older versions of the Engine (e.g. 4.22.3). Use following code:
			Features::Debug::world.isSplitScreen = false;
		*/
		Features::Debug::world.isSplitScreen = SDK::UKismetSystemLibrary::IsSplitScreen(world);
		Features::Debug::world.isStandalone = SDK::UKismetSystemLibrary::IsStandalone(world);
	}


	if (Features::Debug::wasProjectNameObtained == false)
	{
		std::string projectName = SDK::UKismetSystemLibrary::GetGameName().ToString();
		if (projectName.empty() == false)
		{
			Features::Debug::projectName = projectName;
			Features::Debug::wasProjectNameObtained = true;
		}
	}


	if (Features::Debug::wasProjectPlatformObtained == false)
	{
		std::string projectPlatform = SDK::UGameplayStatics::GetPlatformName().ToString();
		if (projectPlatform.empty() == false)
		{
			Features::Debug::projectPlatform = projectPlatform;
			Features::Debug::wasProjectPlatformObtained = true;
		}
	}


	if (Features::Debug::wasEngineVersionObtained == false)
	{
		std::string engineVersion = SDK::UKismetSystemLibrary::GetEngineVersion().ToString();
		if (engineVersion.empty() == false)
		{
			Features::Debug::engineVersion = engineVersion;
			Features::Debug::wasEngineVersionObtained = true;
		}
	}


	if (Features::Debug::wasUsernameObtained == false)
	{
		std::string username = SDK::UKismetSystemLibrary::GetPlatformUserName().ToString();
		if (username.empty() == false)
		{
			Features::Debug::username = username;
			Features::Debug::wasUsernameObtained = true;
		}
	}


	if (Features::Debug::wasCommandLineObtained == false)
	{
		Features::Debug::commandLine = Utilities::CommandLine::Get();
		Features::Debug::wasCommandLineObtained = true;
	}


	Features::Debug::lastUpdateTime = ImGui::GetTime();
}

void Features::Debug::Update_ThreadSafe()
{
	__try
	{
		Features::Debug::Update();
	}
	__except (EXCEPTION()) {}
}




Unreal::Actor::DataStructure Features::ActorsList::GetActorData(SDK::AActor* actorReference)
{
	Unreal::Actor::DataStructure actorData = {};

	if (actorReference == nullptr)
		return actorData;

	actorData.reference = actorReference;

	Unreal::Class::Hierarchy classHierarchy = Unreal::Class::GetClassHierarchy(actorReference);
	actorData.className = classHierarchy.derivedClass->GetFullName();
	for (SDK::UClass* superClass : classHierarchy.superClasses)
	{
		actorData.superClassesNames.push_back(superClass->GetFullName());
	}

	actorData.objectName = actorReference->GetFullName();

	actorData.kind = Unreal::Actor::GetActorKind(actorReference);

	actorData.transform = Unreal::Actor::GetTransform(actorReference);


	std::vector<SDK::UActorComponent*> foundComponents = Unreal::ActorComponent::GetAll(actorReference);
	for (SDK::UActorComponent* component : foundComponents)
	{
		Unreal::ActorComponent::DataStructure componentData = {};

		componentData.reference = component;
		componentData.className = component->Class->GetFullName();
		componentData.objectName = component->GetFullName();

		actorData.components.push_back(componentData);
	}

	return actorData;
}

void Features::ActorsList::Update()
{
	Features::ActorsList::actors.clear();

	std::vector<SDK::AActor*> foundActors = Unreal::Actor::GetAll();
	for (SDK::AActor* actor : foundActors)
	{
		Features::ActorsList::actors.push_back(GetActorData(actor));
	}
}

void Features::ActorsList::Update(const Unreal::Actor::DataStructure& actor)
{
	if (actor.reference == nullptr)
		return;

	for (Unreal::Actor::DataStructure& currentActor : Features::ActorsList::actors) // <-- Reference!
	{
		if (currentActor.reference == actor.reference)
		{
			currentActor = GetActorData(actor.reference);
			return;
		}
	}
}

void Features::ActorsList::Filter()
{
	/* Filter Actors by "Search Filter" */
	switch (Features::ActorsList::filterMode)
	{
		case ImGui::E_ObjectFilterMode::ClassName:
			Features::ActorsList::filteredActors = Unreal::Actor::FilterByClassName(Features::ActorsList::actors, Features::ActorsList::filterBuffer, Features::ActorsList::filterCaseSensitive, Math::Metre_ToUnit(Features::ActorsList::filterDistance));
			break;

		case ImGui::E_ObjectFilterMode::ObjectName:
			Features::ActorsList::filteredActors = Unreal::Actor::FilterByObjectName(Features::ActorsList::actors, Features::ActorsList::filterBuffer, Features::ActorsList::filterCaseSensitive, Math::Metre_ToUnit(Features::ActorsList::filterDistance));
			break;

		case ImGui::E_ObjectFilterMode::All:
			Features::ActorsList::filteredActors = Unreal::Actor::FilterByClassAndObjectName(Features::ActorsList::actors, Features::ActorsList::filterBuffer, Features::ActorsList::filterCaseSensitive, Math::Metre_ToUnit(Features::ActorsList::filterDistance));
			break;
	}
}




Unreal::UserWidget::DataStructure Features::WidgetsList::GetWidgetData(SDK::UUserWidget* widgetReference)
{
	Unreal::UserWidget::DataStructure widgetData = {};

	if (widgetReference == nullptr)
		return widgetData;

	widgetData.reference = widgetReference;

	Unreal::Class::Hierarchy classHierarchy = Unreal::Class::GetClassHierarchy(widgetReference);
	widgetData.className = classHierarchy.derivedClass->GetFullName();
	for (SDK::UClass* superClass : classHierarchy.superClasses)
	{
		widgetData.superClassesNames.push_back(superClass->GetFullName());
	}

	widgetData.objectName = widgetReference->GetFullName();

	widgetData.isTopLevel = widgetReference->IsInViewport();

	if (SDK::UPanelWidget* panelWidget = widgetReference->GetParent())
	{
		widgetData.parent.reference = panelWidget;

		Unreal::Class::Hierarchy classHierarchy = Unreal::Class::GetClassHierarchy(panelWidget);
		widgetData.parent.className = classHierarchy.derivedClass->GetFullName();
		for (SDK::UClass* superClass : classHierarchy.superClasses)
		{
			widgetData.parent.superClassesNames.push_back(superClass->GetFullName());
		}

		widgetData.parent.objectName = panelWidget->GetFullName();
	}

	widgetData.cachedGeometry = widgetReference->GetCachedGeometry();
	widgetData.absolutePosition = SDK::USlateBlueprintLibrary::LocalToAbsolute(widgetData.cachedGeometry, { 0.0f, 0.0f });
	widgetData.absoluteSize = SDK::USlateBlueprintLibrary::GetAbsoluteSize(widgetData.cachedGeometry);
	widgetData.isRendered = widgetData.absoluteSize.IsZero() == false;

	return widgetData;
}

void Features::WidgetsList::Update()
{
	Features::WidgetsList::widgets.clear();

	std::vector<SDK::UUserWidget*> foundWidgets = Unreal::UserWidget::GetAll();
	for (SDK::UUserWidget* widget : foundWidgets)
	{
		Features::WidgetsList::widgets.push_back(GetWidgetData(widget));
	}
}

void Features::WidgetsList::Update(const Unreal::UserWidget::DataStructure& widget)
{
	if (widget.reference == nullptr)
		return;

	for (Unreal::UserWidget::DataStructure& currentWidget : Features::WidgetsList::widgets) // <-- Reference!
	{
		if (currentWidget.reference == widget.reference)
		{
			currentWidget = GetWidgetData(widget.reference);
			return;
		}
	}
}

void Features::WidgetsList::Filter()
{
	/* Filter User Widgets by "Search Filter" */
	switch (Features::WidgetsList::filterMode)
	{
		case ImGui::E_ObjectFilterMode::ClassName:
			Features::WidgetsList::filteredWidgets = Unreal::UserWidget::FilterByClassName(Features::WidgetsList::widgets, Features::WidgetsList::filterBuffer, Features::WidgetsList::filterCaseSensitive, Features::WidgetsList::filterTopLevelOnly, Features::WidgetsList::filterRenderedOnly);
			break;

		case ImGui::E_ObjectFilterMode::ObjectName:
			Features::WidgetsList::filteredWidgets = Unreal::UserWidget::FilterByObjectName(Features::WidgetsList::widgets, Features::WidgetsList::filterBuffer, Features::WidgetsList::filterCaseSensitive, Features::WidgetsList::filterTopLevelOnly, Features::WidgetsList::filterRenderedOnly);
			break;

		case ImGui::E_ObjectFilterMode::All:
			Features::WidgetsList::filteredWidgets = Unreal::UserWidget::FilterByClassAndObjectName(Features::WidgetsList::widgets, Features::WidgetsList::filterBuffer, Features::WidgetsList::filterCaseSensitive, Features::WidgetsList::filterTopLevelOnly, Features::WidgetsList::filterRenderedOnly);
			break;
	}
}




void Features::WidgetVisualisation::Draw()
{
	if (widgetToVisualise.reference == nullptr)
		return;

	if (widgetToVisualise.isRendered == false)
		return;

	if (ImDrawList* drawList = ImGui::GetDrawList())
	{
		ImVec2 p_min = ImVec2(widgetToVisualise.absolutePosition.X, widgetToVisualise.absolutePosition.Y);
		ImVec2 p_max = ImVec2(widgetToVisualise.absolutePosition.X + widgetToVisualise.absoluteSize.X, widgetToVisualise.absolutePosition.Y + widgetToVisualise.absoluteSize.Y);

		ImVec2 p_top_right = ImVec2(p_max.x, p_min.y);
		ImVec2 p_bottom_left = ImVec2(p_min.x, p_max.y);

		ImU32 color = ImGui::ColorConvertFloat4ToU32(ImVec4(Features::WidgetVisualisation::color[0], Features::WidgetVisualisation::color[1], Features::WidgetVisualisation::color[2], Features::WidgetVisualisation::color[3]));
		float lineThickness = Features::WidgetVisualisation::lineThickness;

		drawList->AddRect(p_min, p_max, color, 0.0f, 0, lineThickness);

		drawList->AddLine(p_min, p_max, color, lineThickness);
		drawList->AddLine(p_bottom_left, p_top_right, color, lineThickness);
	}
}

void Features::WidgetVisualisation::Draw_ThreadSafe()
{
	__try
	{
		Features::WidgetVisualisation::Draw();
	}
	__except (EXCEPTION()) {}
}




Unreal::Object::DataStructure Features::ObjectsList::GetObjectData(SDK::UObject* objectReference)
{
	Unreal::Object::DataStructure objectData = {};

	if (objectReference == nullptr)
		return objectData;

	objectData.reference = objectReference;

	Unreal::Class::Hierarchy classHierarchy = Unreal::Class::GetClassHierarchy(objectReference);
	objectData.className = classHierarchy.derivedClass->GetFullName();
	for (SDK::UClass* superClass : classHierarchy.superClasses)
	{
		objectData.superClassesNames.push_back(superClass->GetFullName());
	}

	objectData.objectName = objectReference->GetFullName();

	return objectData;
}

void Features::ObjectsList::Update()
{
	Features::ObjectsList::objects.clear();

	static const std::vector<SDK::TSubclassOf<SDK::UObject>> excludeClasses =
	{
		SDK::AActor::StaticClass(), // Actors List.
		SDK::UActorComponent::StaticClass(), // Actors List -> Actor -> Components.
		SDK::UUserWidget::StaticClass() // Widgets List.
	};
	std::vector<SDK::UObject*> foundObjects = Unreal::Object::GetAll(excludeClasses);
	for (SDK::UObject* object : foundObjects)
	{
		Features::ObjectsList::objects.push_back(GetObjectData(object));
	}
}

void Features::ObjectsList::Update(const Unreal::Object::DataStructure& object)
{
	if (object.reference == nullptr)
		return;

	for (Unreal::Object::DataStructure& currentObject : Features::ObjectsList::objects) // <-- Reference!
	{
		if (currentObject.reference == object.reference)
		{
			currentObject = GetObjectData(object.reference);
			return;
		}
	}
}

void Features::ObjectsList::Filter()
{
	/* Filter Objects by "Search Filter" */
	switch (Features::ObjectsList::filterMode)
	{
		case ImGui::E_ObjectFilterMode::ClassName:
			Features::ObjectsList::filteredObjects = Unreal::Object::FilterByClassName(Features::ObjectsList::objects, Features::ObjectsList::filterBuffer, Features::ObjectsList::filterCaseSensitive);
			break;

		case ImGui::E_ObjectFilterMode::ObjectName:
			Features::ObjectsList::filteredObjects = Unreal::Object::FilterByObjectName(Features::ObjectsList::objects, Features::ObjectsList::filterBuffer, Features::ObjectsList::filterCaseSensitive);
			break;

		case ImGui::E_ObjectFilterMode::All:
			Features::ObjectsList::filteredObjects = Unreal::Object::FilterByClassAndObjectName(Features::ObjectsList::objects, Features::ObjectsList::filterBuffer, Features::ObjectsList::filterCaseSensitive);
			break;
	}
}




void Features::CharacterMovement::Ghost()
{
	bool wasSuccessfull = Unreal::Character::Ghost(0);
	GUI::PlayActionSound(wasSuccessfull);
}

void Features::CharacterMovement::Fly()
{
	bool wasSuccessfull = Unreal::Character::Fly(0);
	GUI::PlayActionSound(wasSuccessfull);
}

void Features::CharacterMovement::Walk()
{
	bool wasSuccessfull = Unreal::Character::Walk(0);
	GUI::PlayActionSound(wasSuccessfull);
}




void Features::CharacterMovement::Jump()
{
	bool wasSuccessfull = Unreal::Character::Jump(0);
	GUI::PlayActionSound(wasSuccessfull);
}




void Features::CharacterMovement::Launch()
{
	SDK::FVector launchVelocity = { Features::CharacterMovement::launchVelocity[0], Features::CharacterMovement::launchVelocity[1], Features::CharacterMovement::launchVelocity[2] };

	bool wasSuccessfull = Unreal::Character::Launch(0, launchVelocity);
	GUI::PlayActionSound(wasSuccessfull);
}

void Features::CharacterMovement::Dash()
{
	SDK::ACharacter* character = Unreal::Character::Get();
	if (character == nullptr)
	{
		GUI::PlayActionSound(false);
		return;
	}

	SDK::FVector forwardVector = character->GetActorForwardVector();

	/* Dash shouldn't involve any vertical movement. */
	forwardVector.Z = 0.0;
	forwardVector.Normalize();

	SDK::FVector launchVelocity = forwardVector * Features::CharacterMovement::dashStrength;

	bool wasSuccessfull = Unreal::Character::Launch(character, launchVelocity);
	GUI::PlayActionSound(wasSuccessfull);
}




void Features::Camera::StartFade()
{
	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr || playerController->PlayerCameraManager == nullptr)
	{
		GUI::PlayActionSound(false);
		return;
	}

	SDK::FLinearColor fadeColor;
	fadeColor.R = Features::Camera::fadeColor[0];
	fadeColor.G = Features::Camera::fadeColor[1];
	fadeColor.B = Features::Camera::fadeColor[2];
	fadeColor.A = Features::Camera::fadeColor[3];

	playerController->PlayerCameraManager->StartCameraFade(Features::Camera::fadeFromAlpha, Features::Camera::fadeToAlpha, Features::Camera::fadeDuration, fadeColor, Features::Camera::fadeAudio, Features::Camera::fadePersistent);
	GUI::PlayActionSound(true);
}

void Features::Camera::StopFade()
{
	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr || playerController->PlayerCameraManager == nullptr)
	{
		GUI::PlayActionSound(false);
		return;
	}

	playerController->PlayerCameraManager->StopCameraFade();
	GUI::PlayActionSound(true);
}






bool Features::Positions::ReadPositionFromConfig(ConfigInstance* positionsConfig, int32_t positionId, Positions::PositionEntry* positionEntry)
{
	if (positionsConfig == nullptr || positionEntry == nullptr)
		return false;

	std::string entryName_Base = Positions::entryPrefix + std::to_string(positionId);
	std::string entryName_Title = entryName_Base + Positions::entryTitleSuffix;
	std::string entryName_Location = entryName_Base + Positions::entryLocationSuffix;
	std::string entryName_Rotation = entryName_Base + Positions::entryRotationSuffix;

	if (positionsConfig->HasKey(entryName_Title) == false || positionsConfig->HasKey(entryName_Location) == false)
		return false;

	positionEntry->title = positionsConfig->GetKey<std::string>(entryName_Title).value_or(std::string());

	std::array<float, 3> location = positionsConfig->GetKey<std::array<float, 3>>(entryName_Location).value_or({ 0.0f, 0.0f, 0.0f });
	positionEntry->location = { location[0], location[1], location[2] };

	std::array<float, 3> rotation = positionsConfig->GetKey<std::array<float, 3>>(entryName_Rotation).value_or({ 0.0f, 0.0f, 0.0f });
	positionEntry->rotation = { rotation[0], rotation[1], rotation[2] };

	return true;
}

void Features::Positions::Load()
{
	ConfigInstance positionsConfig(PATH_CONFIG_POSITIONS);
	if (positionsConfig.Load() == false)
	{
		Features::Positions::Save();
		positionsConfig.Load();
	}

	std::vector<Positions::PositionEntry> outVector;
	for (int32_t i = 0; i < Features::Positions::entriesLimit; i++)
	{
		Positions::PositionEntry entry{};
		if (ReadPositionFromConfig(&positionsConfig, i, &entry) == false)
			break;

		outVector.push_back(entry);
	}

	Positions::entries = outVector;
}

void Features::Positions::Save()
{
	ConfigInstance positionsConfig(PATH_CONFIG_POSITIONS);

	int32_t entriesCount = Positions::entries.size();
	for (int32_t i = 0; i < entriesCount; i++)
	{
		std::string entryName_Base = Positions::entryPrefix + std::to_string(i);
		std::string entryName_Title = entryName_Base + Positions::entryTitleSuffix;
		std::string entryName_Location = entryName_Base + Positions::entryLocationSuffix;
		std::string entryName_Rotation = entryName_Base + Positions::entryRotationSuffix;

		positionsConfig.SetKey(entryName_Title, entries[i].title);

		std::array<float, 3> location = { entries[i].location.X, entries[i].location.Y, entries[i].location.Z };
		positionsConfig.SetKey(entryName_Location, location);

		std::array<float, 3> rotation = { entries[i].rotation.Pitch, entries[i].rotation.Yaw, entries[i].rotation.Roll };
		positionsConfig.SetKey(entryName_Rotation, rotation);
	}

	positionsConfig.Save();
}




bool Features::ActorTrace::Trace()
{
	SDK::UWorld* world = Unreal::World::Get();
	if (world == nullptr)
		return false;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr || playerController->PlayerCameraManager == nullptr)
		return false;

	SDK::FVector cameraLocation = Unreal::Actor::GetLocation(playerController->PlayerCameraManager);
	SDK::FVector cameraForwardVector = playerController->PlayerCameraManager->GetActorForwardVector();
	SDK::FVector traceEndLocation = cameraLocation + (cameraForwardVector * Math::Metre_ToUnit(Features::ActorTrace::traceDistance));

	SDK::TArray<SDK::AActor*> actorsToIgnore;
	if (SDK::ACharacter* character = Unreal::Character::Get())
		actorsToIgnore.Add(character);

	SDK::FHitResult hitResult;
	Features::ActorTrace::traceHit = SDK::UKismetSystemLibrary::LineTraceSingle(world, cameraLocation, traceEndLocation, SDK::ETraceTypeQuery::TraceTypeQuery1, false, actorsToIgnore, SDK::EDrawDebugTrace::ForDuration, &hitResult, true, SDK::FLinearColor(), SDK::FLinearColor(), 5.0f);
	if (traceHit)
	{
		Features::ActorTrace::traceStartLocation = cameraLocation;
		Features::ActorTrace::traceEndLocation = hitResult.Location;

#ifdef UE5
		/* UE 5.3.2 and older: hitResult.HitObjectHandle.Actor.Get() */
		SDK::UObject* hitObject = hitResult.HitObjectHandle.ReferenceObject.Get();
		if (hitObject)
		{
			Features::ActorTrace::object.reference = hitObject;
			Features::ActorTrace::object.className = hitObject->Class->GetFullName();
			Features::ActorTrace::object.objectName = hitObject->GetFullName();
		}
#else
		SDK::AActor* hitActor = hitResult.Actor.Get();
		if (hitActor)
		{
			Features::ActorTrace::actor.reference = hitActor;
			Features::ActorTrace::actor.className = hitActor->Class->GetFullName();
			Features::ActorTrace::actor.objectName = hitActor->GetFullName();
		}
#endif
	}
	else
	{
		Features::ActorTrace::traceStartLocation = cameraLocation;
		Features::ActorTrace::traceEndLocation = traceEndLocation;
	}

	Features::ActorTrace::traceCast = true;
	return true;
}


void Features::ActorTrace::Draw()
{
	if (ImDrawList* drawList = ImGui::GetDrawList())
	{
		if (Features::ActorTrace::showOnScreen && Features::ActorTrace::traceCast)
		{
			SDK::FVector2D screenStartPosition;
			SDK::FVector2D screenEndPosition;

			/* UGameplayStatics::ProjectWorldToScreen() verify Player Controller reference within its code. */
			SDK::APlayerController* playerController = Unreal::PlayerController::Get();
			bool startPositionProjected = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, Features::ActorTrace::traceStartLocation, &screenStartPosition, false);
			bool endPositionProjected = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, Features::ActorTrace::traceEndLocation, &screenEndPosition, false);

			/* Inverse Normalize RGBA values set by color picker. */
			ImU32 color = ImGui::ColorConvertFloat4ToU32(ImVec4(Features::ActorTrace::traceColor[0], Features::ActorTrace::traceColor[1], Features::ActorTrace::traceColor[2], Features::ActorTrace::traceColor[3]));

			static float traceStartCircleRadius;
			if (startPositionProjected)
				traceStartCircleRadius = Features::ActorTrace::traceThickness * 1.5f;

			static float traceEndCircleRadius;
			static float traceCrossSize;
			if (endPositionProjected)
			{
				traceEndCircleRadius = Features::ActorTrace::traceThickness * 1.75f;
				traceCrossSize = 8.0f + (Features::ActorTrace::traceThickness * 0.5f);
			}

			/* Both start and end position are within player view. */
			if (startPositionProjected && endPositionProjected)
			{
				ImVec2 startPosition = { (float)screenStartPosition.X, (float)screenStartPosition.Y };
				ImVec2 endPosition = { (float)screenEndPosition.X, (float)screenEndPosition.Y };

				/* Draw the trace. */
				drawList->AddLine(startPosition, endPosition, color, Features::ActorTrace::traceThickness);

				/* Draw a hollow circle to mark position where trace was sent from. */
				drawList->AddCircle(startPosition, traceStartCircleRadius, color);

				/*
					If trace has hit something, draw a cross to mark position where the trace hit;
					Otherwise draw a filled circle to mark position where the trace ends.
				*/
				if (Features::ActorTrace::traceHit)
				{
					drawList->AddLine({ endPosition.x - traceCrossSize, endPosition.y - traceCrossSize }, { endPosition.x + traceCrossSize, endPosition.y + traceCrossSize }, color, Features::ActorTrace::traceThickness);
					drawList->AddLine({ endPosition.x - traceCrossSize, endPosition.y + traceCrossSize }, { endPosition.x + traceCrossSize, endPosition.y - traceCrossSize }, color, Features::ActorTrace::traceThickness);
				}
				else
					drawList->AddCircleFilled(endPosition, traceEndCircleRadius, color);
			}
			/* Only start position is within player view. */
			else if (startPositionProjected)
			{
				ImVec2 position = { (float)screenStartPosition.X, (float)screenStartPosition.Y };

				drawList->AddCircle(position, traceStartCircleRadius, color);
			}
			/* Only end position is within player view. */
			else if (endPositionProjected)
			{
				ImVec2 position = { (float)screenEndPosition.X, (float)screenEndPosition.Y };

				if (Features::ActorTrace::traceHit)
				{
					drawList->AddLine({ position.x - traceCrossSize, position.y - traceCrossSize }, { position.x + traceCrossSize, position.y + traceCrossSize }, color, Features::ActorTrace::traceThickness);
					drawList->AddLine({ position.x - traceCrossSize, position.y + traceCrossSize }, { position.x + traceCrossSize, position.y - traceCrossSize }, color, Features::ActorTrace::traceThickness);
				}
				else
					drawList->AddCircleFilled(position, traceEndCircleRadius, color);
			}


			if (endPositionProjected)
			{
#ifdef UE5
				const char* labelText = Features::ActorTrace::traceHit ? Features::ActorTrace::object.objectName.c_str() : "No Object Traced";
#else
				const char* labelText = Features::ActorTrace::traceHit ? Features::ActorTrace::actor.objectName.c_str() : "No Actor Traced";
#endif
				ImVec2 labelSize = ImGui::CalcTextSize(labelText);

				ImVec2 labelPosition = 
				{ 
					/* Flooring the values allows to avoid potential subpixel conflicts. */
					floorf(screenEndPosition.X - (labelSize.x * 0.5)),
					floorf((float)screenEndPosition.Y - 36.0f)
				};

				drawList->AddText(labelPosition, color, labelText);
			}
		}
	}
}

void Features::ActorTrace::Draw_ThreadSafe()
{
	__try
	{
		Features::ActorTrace::Draw();
	}
	__except (EXCEPTION()) {}
}




void Features::ActorsTracker::Draw()
{
	if (SDK::APlayerController* playerController = Unreal::PlayerController::Get())
	{
		if (ImDrawList* drawList = ImGui::GetDrawList())
		{
			SDK::FVector playerLocation = Unreal::PlayerController::GetLocation(playerController);

			for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
			{
				SDK::FVector2D screenPosition;
				if (SDK::UGameplayStatics::ProjectWorldToScreen(playerController, actor.transform.location, &screenPosition, false))
				{
					bool isValid = Unreal::Actor::IsValid(actor.reference);

					float distanceUnit = Math::Vector_Distance(playerLocation, actor.transform.location);
					float distanceMetres = Math::Unit_ToMetre(distanceUnit);

					float alphaModifier = 1.0f;
					if (Features::ActorsTracker::fadeOnCloseup)
					{
						alphaModifier = distanceMetres / 10.0f;

						if (alphaModifier < 0.10f)
							alphaModifier = 0.10f;

						if (alphaModifier > 1.0f)
							alphaModifier = 1.0f;
					}

					float colorWithAlphaModifier[4] =
					{
						Features::ActorsTracker::actorColor[0],
						Features::ActorsTracker::actorColor[1],
						Features::ActorsTracker::actorColor[2],
						Features::ActorsTracker::actorColor[3] * alphaModifier
					};
					ImU32 actorColor = Math::ColorFloat4_ToU32(colorWithAlphaModifier);
					ImTextureID actorIcon = isValid ? ImGui::Texture2D::Get(Window::texturesCollection.T_Friendly) : ImGui::Texture2D::Get(Window::texturesCollection.T_Hostile);

					static float iconSize = 32.0f;
					static float halfSize = iconSize * 0.5f;

					ImVec2 p_min = ImVec2(floorf(screenPosition.X - halfSize), floorf(screenPosition.Y - halfSize));
					ImVec2 p_max = ImVec2(floorf(screenPosition.X + halfSize), floorf(screenPosition.Y + halfSize));

					if (ImGui::Texture2D::IsValid(actorIcon))
					{
						ImU32 iconColor = IM_COL32(255, 255, 255, static_cast<int>(255.0f * alphaModifier));
						drawList->AddImage(actorIcon, p_min, p_max, ImVec2(0, 0), ImVec2(1, 1), iconColor);
					}
					else
					{
						ImVec4 baseColor = ImGui::ColorConvertU32ToFloat4(isValid ? ImGui::Color::Green : ImGui::Color::Red);
						baseColor.w *= alphaModifier;

						ImU32 circleColor = ImGui::ColorConvertFloat4ToU32(baseColor);
						drawList->AddCircleFilled({ (float)screenPosition.X, (float)screenPosition.Y }, 16.0f, circleColor);
					}

					const char* labelText = actor.objectName.c_str();
					ImVec2 labelSize = ImGui::CalcTextSize(labelText);
					ImVec2 labelPosition = ImVec2
					(
						/* Flooring the values allows to avoid potential subpixel conflicts. */
						floorf(screenPosition.X - (labelSize.x * 0.5)),
						floorf(screenPosition.Y - 40.0f)
					);
					drawList->AddText(labelPosition, actorColor, labelText);

					if (Features::ActorsTracker::showDistance)
					{
						std::string distanceString = std::format("{:.0f}m", distanceMetres);

						ImVec2 distanceSize = ImGui::CalcTextSize(distanceString.c_str());
						ImVec2 distancePosition = ImVec2
						(
							/* Flooring the values allows to avoid potential subpixel conflicts. */
							floorf(screenPosition.X - (distanceSize.x * 0.5)),
							floorf(screenPosition.Y + 24.0f)
						);
						drawList->AddText(distancePosition, actorColor, distanceString.c_str());
					}
				}
			}
		}
	}
}

void Features::ActorsTracker::Draw_ThreadSafe()
{
	__try
	{
		Features::ActorsTracker::Draw();
	}
	__except (EXCEPTION()) {}
}




#ifdef COLLISION_VISUALIZER
void Features::CollisionVisualizer::Draw()
{
	/* UGameplayStatics::ProjectWorldToScreen() verify Player Controller reference within its code. */
	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController)
	{
		SDK::FVector playerLocation = Unreal::PlayerController::GetLocation(0);
	
		for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
		{
			if (actor.reference == nullptr)
				continue;
	
			if (actor.reference->IsA(SDK::AVolume::StaticClass()))
			{
				if (actor.reference->IsA(SDK::APhysicsVolume::StaticClass()))
				{
					DebugDraw::DrawVolume(static_cast<SDK::AVolume*>(actor.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_PhysicsVolume), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				if (actor.reference->IsA(SDK::ABlockingVolume::StaticClass()))
				{
					DebugDraw::DrawVolume(static_cast<SDK::AVolume*>(actor.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_BlockingVolume), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				if (actor.reference->IsA(SDK::ATriggerVolume::StaticClass()))
				{
					DebugDraw::DrawVolume(static_cast<SDK::AVolume*>(actor.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_TriggerVolume), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				if (actor.reference->IsA(SDK::APostProcessVolume::StaticClass()))
				{
					DebugDraw::DrawVolume(static_cast<SDK::AVolume*>(actor.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_PostProcessVolume), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				DebugDraw::DrawVolume(static_cast<SDK::AVolume*>(actor.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_Other), Features::CollisionVisualizer::thickness);
				continue;
			}
	
	
			for (Unreal::ActorComponent::DataStructure& actorComponent : actor.components) // <-- Reference!
			{
				if (actorComponent.reference == nullptr)
					continue;
	
				/* #1 Static Mesh. */
				if (actorComponent.reference->IsA(SDK::UStaticMeshComponent::StaticClass()))
				{
					DebugDraw::DrawStaticMeshComponent(static_cast<SDK::UStaticMeshComponent*>(actorComponent.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_StaticMesh), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				/* #2 Instanced Static Mesh. */
				if (actorComponent.reference->IsA(SDK::UInstancedStaticMeshComponent::StaticClass()))
				{
					DebugDraw::DrawInstancedStaticMeshComponent(static_cast<SDK::UInstancedStaticMeshComponent*>(actorComponent.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_StaticMesh), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				/* #3 Skeletal Mesh. */
				if (actorComponent.reference->IsA(SDK::USkeletalMeshComponent::StaticClass()))
				{
					DebugDraw::DrawSkeletalMeshComponent(static_cast<SDK::USkeletalMeshComponent*>(actorComponent.reference), false, Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_Other), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				/* #4 Capsule Component. */
				if (actorComponent.reference->IsA(SDK::UCapsuleComponent::StaticClass()))
				{
					DebugDraw::DrawCapsuleComponent(static_cast<SDK::UCapsuleComponent*>(actorComponent.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_Primitive), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				/* #5 Sphere Component. */
				if (actorComponent.reference->IsA(SDK::USphereComponent::StaticClass()))
				{
					DebugDraw::DrawSphereComponent(static_cast<SDK::USphereComponent*>(actorComponent.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_Primitive), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				/* #6 Box Component. */
				if (actorComponent.reference->IsA(SDK::UBoxComponent::StaticClass()))
				{
					DebugDraw::DrawBoxComponent(static_cast<SDK::UBoxComponent*>(actorComponent.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_Primitive), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				/* #1 Spline Component. */
				if (actorComponent.reference->IsA(SDK::USplineComponent::StaticClass()))
				{
					DebugDraw::DrawSplineComponent(static_cast<SDK::USplineComponent*>(actorComponent.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_Primitive), Features::CollisionVisualizer::thickness);
					continue;
				}
			}
		}
	}
}

void Features::CollisionVisualizer::Draw_ThreadSafe()
{
	__try
	{
		Features::CollisionVisualizer::Draw();
	}
	__except (EXCEPTION()) {}
}
#endif




Unreal::LevelStreaming::DataStructure Features::LevelStreaming::GetLevelStreamingData(SDK::ULevelStreaming* levelStreamingReference)
{
	Unreal::LevelStreaming::DataStructure levelStreamingData = {};

	if (levelStreamingReference == nullptr)
		return levelStreamingData;

#ifdef UE5
	std::string levelPath = levelStreamingReference->WorldAsset.ObjectID.AssetPath.AssetName.GetRawString();
#else
	std::string levelPath = levelStreamingReference->WorldAsset.ObjectID.AssetPathName.GetRawString();
#endif

	if (levelPath.empty())
		return levelStreamingData;

	levelStreamingData.reference = levelStreamingReference;
	levelStreamingData.className = levelStreamingReference->Class->GetFullName();
	levelStreamingData.objectName = levelStreamingReference->GetFullName();

	levelStreamingData.levelPath = levelPath;
	levelStreamingData.levelColor = levelStreamingReference->LevelColor;

	SDK::ULevel* loadedLevel = levelStreamingReference->LoadedLevel;
	if (levelStreamingData.level.reference = loadedLevel)
	{
		levelStreamingData.level.className = loadedLevel->Class->GetFullName();
		levelStreamingData.level.objectName = loadedLevel->GetFullName();

		levelStreamingData.level.isVisible = loadedLevel->bIsVisible;

		SDK::AWorldSettings* worldSettings = loadedLevel->WorldSettings;
		if (levelStreamingData.level.worldSettings.reference = worldSettings)
		{
			levelStreamingData.level.worldSettings.className = worldSettings->Class->GetFullName();
			levelStreamingData.level.worldSettings.objectName = worldSettings->GetFullName();

			levelStreamingData.level.worldSettings.highPriorityLoading = worldSettings->bHighPriorityLoading;
			levelStreamingData.level.worldSettings.localHighPriorityLoading = worldSettings->bHighPriorityLoadingLocal;

			levelStreamingData.level.worldSettings.unitsToMeters = worldSettings->WorldToMeters;
		}
	}

	return levelStreamingData;
}

void Features::LevelStreaming::Update()
{
	levels.clear();

	std::vector<SDK::ULevelStreaming*> levelStreamings = Unreal::LevelStreaming::GetAll();
	for (SDK::ULevelStreaming* lvlStreaming : levelStreamings)
	{
		Features::LevelStreaming::levels.push_back(GetLevelStreamingData(lvlStreaming));
	}
}

void Features::LevelStreaming::Update(const Unreal::LevelStreaming::DataStructure& levelStreaming)
{
	if (levelStreaming.reference == nullptr)
		return;

	for (Unreal::LevelStreaming::DataStructure& currentLevelStreaming : Features::LevelStreaming::levels) // <-- Reference!
	{
		if (currentLevelStreaming.reference == levelStreaming.reference)
		{
			currentLevelStreaming = GetLevelStreamingData(levelStreaming.reference);
			return;
		}
	}
}

void Features::LevelStreaming::Filter()
{
	Features::LevelStreaming::filteredLevels = Unreal::LevelStreaming::FilterByLevelPath(Features::LevelStreaming::levels, Features::LevelStreaming::filterBuffer, Features::LevelStreaming::filterCaseSensitive);
}




bool Features::FreeCamera::IsEnabled()
{
	if (Features::FreeCamera::cameraReference == nullptr)
		return false;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return false;

	SDK::AActor* viewTarget = playerController->GetViewTarget();
	if (viewTarget == nullptr)
		return false;

	return Features::FreeCamera::cameraReference == viewTarget;
}

bool Features::FreeCamera::Enable()
{
	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return false;

	if (Unreal::Actor::IsValid(Features::FreeCamera::cameraReference) == false)
	{
		SDK::AActor* actorReference = Unreal::Actor::Summon(SDK::ACameraActor::StaticClass());
		if (actorReference == nullptr)
			return false;

		Features::FreeCamera::cameraReference = static_cast<SDK::ACameraActor*>(actorReference);
	}

	if (playerController->PlayerCameraManager)
	{
		SDK::APlayerCameraManager* playerCameraManager = playerController->PlayerCameraManager;
		Unreal::Transform playerCameraTransform = Unreal::Actor::GetTransform(playerCameraManager);

		Features::FreeCamera::cameraReference->SetActorEnableCollision(false);
		Features::FreeCamera::cameraReference->FOVAngle = 83.0f;

		Unreal::Actor::TeleportTo(Features::FreeCamera::cameraReference, playerCameraTransform.location, playerCameraTransform.rotation);
	}

	/* Save current view target before attempting to switch. */
	SDK::AActor* currentViewTarget = playerController->GetViewTarget();

	/* Attempt to switch the camera first. */
	Unreal::PlayerController::SetViewTarget(Features::FreeCamera::cameraReference);

	/* Verify that the view target actually changed to our FreeCamera. */
	if (playerController->GetViewTarget() == Features::FreeCamera::cameraReference)
	{
		Features::FreeCamera::lastViewTarget = currentViewTarget;

		/* Apply custom time dilation only after a successful camera switch. */
		if (Features::FreeCamera::lastViewTarget != nullptr)
		{
			if (Features::FreeCamera::forceFreezePlayer)
			{
				Features::FreeCamera::storedCustomTimeDilation = Features::FreeCamera::lastViewTarget->CustomTimeDilation;
				Features::FreeCamera::lastViewTarget->CustomTimeDilation = 0.0f;
			}
			
			if (Features::FreeCamera::forceDisablePlayerInput)
			{
				Features::FreeCamera::wasMoveInputIgnored = playerController->IsMoveInputIgnored();
				playerController->SetIgnoreMoveInput(true);

				Features::FreeCamera::wasLookInputIgnored = playerController->IsLookInputIgnored();
				playerController->SetIgnoreLookInput(true);
			}
		}

		return true;
	}

	/* If ViewTarget failed to switch, do not freeze the player and return False. */
	return false;
}

bool Features::FreeCamera::Disable()
{
	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return false;

	if (Features::FreeCamera::lastViewTarget != nullptr)
	{
		if (Features::FreeCamera::forceFreezePlayer)
		{
			Features::FreeCamera::lastViewTarget->CustomTimeDilation = Features::FreeCamera::storedCustomTimeDilation;
		}

		if (Features::FreeCamera::forceDisablePlayerInput)
		{
			playerController->SetIgnoreMoveInput(Features::FreeCamera::wasMoveInputIgnored);
			playerController->SetIgnoreLookInput(Features::FreeCamera::wasLookInputIgnored);
		}

		Unreal::PlayerController::SetViewTarget(Features::FreeCamera::lastViewTarget);
		Features::FreeCamera::lastViewTarget = nullptr;

		return true;
	}
	else if (playerController->Pawn != nullptr)
	{
		Unreal::PlayerController::SetViewTarget(playerController->Pawn);
		return true;
	}
	else
		return false;
}

void Features::FreeCamera::Toggle()
{
	if (IsEnabled() == false)
	{
		Enable();
		GUI::PlayActionSound(true);
	}
	else
	{
		Disable();
		GUI::PlayActionSound(false);
	}
}


bool Features::FreeCamera::Move(const float forwardStep, const float rightStep, const float upStep)
{
	if (IsEnabled() == false)
		return false;

	Unreal::Transform freeCameraTransform = Unreal::Actor::GetTransform(Features::FreeCamera::cameraReference);
	SDK::FVector forwardVector = Math::Rotator_ForwardVector(freeCameraTransform.rotation);
	SDK::FVector rightVector = Math::Rotator_RightVector(freeCameraTransform.rotation);
	SDK::FVector upVector = Math::Rotator_UpVector(freeCameraTransform.rotation);

	SDK::FVector locationOffset;
	locationOffset = Math::Vector_Add(locationOffset, Math::Vector_Multiply(forwardVector, forwardStep));
	locationOffset = Math::Vector_Add(locationOffset, Math::Vector_Multiply(rightVector, rightStep));
	locationOffset = Math::Vector_Add(locationOffset, Math::Vector_Multiply(upVector, upStep));

	SDK::FVector newLocation = Math::Vector_Add(freeCameraTransform.location, locationOffset);
	return Unreal::Actor::SweepTo(Features::FreeCamera::cameraReference, newLocation);
}

bool Features::FreeCamera::Rotate(const float horizontalStep, const float verticalStep)
{
	if (IsEnabled() == false)
		return false;

	SDK::FRotator freeCameraRotation = Unreal::Actor::GetRotation(Features::FreeCamera::cameraReference);
	freeCameraRotation.Yaw += horizontalStep;

	float newPitch = freeCameraRotation.Pitch + verticalStep;
	freeCameraRotation.Pitch = std::clamp(newPitch, -89.0f, 89.0f);

	freeCameraRotation.Roll = 0.0f;

	return Unreal::Actor::TeleportTo(Features::FreeCamera::cameraReference, freeCameraRotation);
}


bool Features::FreeCamera::TeleportPlayerToCamera()
{
	if (IsEnabled() == false)
		return false;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr || playerController->Pawn == nullptr)
		return false;

	SDK::FVector cameraLocation = Unreal::Actor::GetLocation(Features::FreeCamera::cameraReference);
	return Unreal::Actor::TeleportTo(playerController->Pawn, cameraLocation);
}

bool Features::FreeCamera::TeleportCameraToPlayer()
{
	if (IsEnabled() == false)
		return false;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return false;

	SDK::FVector playerLocation;
	if (Features::FreeCamera::lastViewTarget != nullptr)
		playerLocation = Unreal::Actor::GetLocation(Features::FreeCamera::lastViewTarget);
	else if (playerController->Pawn != nullptr)
		playerLocation = Unreal::Actor::GetLocation(playerController->Pawn);
	else
		return false;

	return Unreal::Actor::TeleportTo(Features::FreeCamera::cameraReference, playerLocation);
}




void Features::ConsoleCommands::Update()
{
	commands.clear();

	std::vector<SDK::UObject*> objects = Unreal::Object::GetAll();
	for (SDK::UObject* objectReference : objects)
	{
		if (objectReference == nullptr)
			continue;

		std::vector<Unreal::Function::DataStructure> functions = Unreal::Function::GetFunctions(objectReference, SDK::EFunctionFlags::Exec);
		commands.insert(commands.end(), functions.begin(), functions.end());
	}

	std::sort(commands.begin(), commands.end(), [](const Unreal::Function::DataStructure& a, const Unreal::Function::DataStructure& b)
	{
		return a.name < b.name;
	});

	auto last = std::unique(commands.begin(), commands.end(), [](const Unreal::Function::DataStructure& a, const Unreal::Function::DataStructure& b)
	{
		return a.name == b.name;
	});

	commands.erase(last, commands.end());
}






void BackgroundTasks::KeybindingsHandler::Worker()
{
	while (isEnabled)
	{
		/* Following inputs are only processed while title window is in focus. */
		if (GUI::GetIsTitleInFocus())
		{
			if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::general_MenuOpenClose))
				GUI::ToggleIsMenuActive();

			if (GUI::GetIsMenuActive() == false)
			{
				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::debug_ActorTrace))
				{
					GUI::PlayActionSound(Features::ActorTrace::Trace());
				}

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::debug_ActorsListUpdate))
				{
					Features::ActorsList::Update();
					Features::ActorsList::Filter();

					GUI::PlayActionSound(true);
				}

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::debug_ActorsListTracking))
				{
					if (Features::ActorsTracker::enabled)
						Features::ActorsTracker::enabled = false;
					else
					{
						Features::ActorsList::Update();

						if (Features::ActorsList::filterDistance == 0.0f)
							Features::ActorsList::filterDistance = 20.0f;

						Features::ActorsList::Filter();

						Features::ActorsTracker::enabled = true;
					}

					GUI::PlayActionSound(true);
				}

#ifdef COLLISION_VISUALIZER
				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::debug_ActorsListCollisionDraw))
				{
					if (Features::CollisionVisualizer::enabled)
						Features::CollisionVisualizer::enabled = false;
					else
					{
						Features::ActorsList::Update();

						if (Features::ActorsList::filterDistance == 0.0f)
							Features::ActorsList::filterDistance = 20.0f;

						Features::ActorsList::Filter();

						Features::CollisionVisualizer::enabled = true;
					}

					GUI::PlayActionSound(true);
				}
#endif




				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::characterMovement_Ghost))
				{
					Features::CharacterMovement::Ghost();
				}

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::characterMovement_Fly))
				{
					Features::CharacterMovement::Fly();
				}

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::characterMovement_Walk))
				{
					Features::CharacterMovement::Walk();
				}

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::characterMovement_Jump))
				{
					Features::CharacterMovement::Jump();
				}

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::characterMovement_Launch))
				{
					Features::CharacterMovement::Launch();
				}

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::characterMovement_Dash))
				{
					Features::CharacterMovement::Dash();
				}




				if (Features::DirectionalMovement::omniMovement)
				{
					Features::DirectionalMovement::isUpMovementExpected = ImGui::IsKeyBindingDown(&Inputs::Keybindings::characterOmniMovement_Up);
					Features::DirectionalMovement::isDownMovementExpected = ImGui::IsKeyBindingDown(&Inputs::Keybindings::characterOmniMovement_Down);

					if (Features::DirectionalMovement::independentOmniMovement)
					{
						Features::DirectionalMovement::isForwardMovementExpected = ImGui::IsKeyBindingDown(&Inputs::Keybindings::characterOmniMovement_Forward);
						Features::DirectionalMovement::isBackwardMovementExpected = ImGui::IsKeyBindingDown(&Inputs::Keybindings::characterOmniMovement_Backward);
						Features::DirectionalMovement::isLeftMovementExpected = ImGui::IsKeyBindingDown(&Inputs::Keybindings::characterOmniMovement_Left);
						Features::DirectionalMovement::isRightMovementExpected = ImGui::IsKeyBindingDown(&Inputs::Keybindings::characterOmniMovement_Right);
					}
				}




				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::characterCamera_StartFade))
				{
					Features::Camera::StartFade();
				}

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::characterCamera_StopFade))
				{
					Features::Camera::StopFade();
				}




				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::freeCamera_Toggle))
				{
					Features::FreeCamera::Toggle();
				}

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::freeCamera_TeleportPlayerToCamera))
				{
					GUI::PlayActionSound(Features::FreeCamera::TeleportPlayerToCamera());
				}

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::freeCamera_TeleportCameraToPlayer))
				{
					GUI::PlayActionSound(Features::FreeCamera::TeleportCameraToPlayer());
				}

				if (Features::FreeCamera::cameraReference)
				{
					static bool wasMouseControlActive = false;
					if (Features::FreeCamera::useMouseControl && Features::FreeCamera::IsEnabled())
					{
						bool mouseControlExpected = true;
						if (Features::FreeCamera::mouseControlOnHold)
						{
							mouseControlExpected = ImGui::IsMouseButtonDown(ImGui::E_MouseButton::Right);
						}

						if (mouseControlExpected)
						{
							int screenWidth = GetSystemMetrics(SM_CXSCREEN);
							int screenHeight = GetSystemMetrics(SM_CYSCREEN);

							POINT screenCenter;
							screenCenter.x = screenWidth / 2;
							screenCenter.y = screenHeight / 2;

							if (wasMouseControlActive == false)
							{
								SetCursorPos(screenCenter.x, screenCenter.y);
							}
							else
							{
								POINT currentMousePos;
								if (GetCursorPos(&currentMousePos))
								{
									float mouseDeltaX = static_cast<float>(currentMousePos.x - screenCenter.x);
									float mouseDeltaY = static_cast<float>(currentMousePos.y - screenCenter.y);

									/*
										Some users have reported erratic mouse behavior
										after interacting with the menu until they press LMB.

										While the exact cause of this inconsistency is unknown,
										following code tries to resolve the issue.
									*/
									if (Features::FreeCamera::mouseControlLimitMaximumDelta && (std::abs(mouseDeltaX) > Features::FreeCamera::mouseControlMaximumDelta || std::abs(mouseDeltaY) > Features::FreeCamera::mouseControlMaximumDelta))
									{
										SetCursorPos(screenCenter.x, screenCenter.y);
									}
									else if (mouseDeltaX != 0.0f || mouseDeltaY != 0.0f)
									{
										/* X -> Yaw (horizontal). */
										float horizontalStep = mouseDeltaX * Features::FreeCamera::mouseControlSensitivity;
										if (Features::FreeCamera::mouseControlXInverted)
											horizontalStep *= -1.0f;

										/* Y -> Pitch (vertical). */
										float verticalStep = mouseDeltaY * Features::FreeCamera::mouseControlSensitivity;
										if (Features::FreeCamera::mouseControlYInverted)
											verticalStep *= -1.0f;

										Features::FreeCamera::Rotate(horizontalStep, verticalStep);
										SetCursorPos(screenCenter.x, screenCenter.y);
									}
								}
							}
						}

						wasMouseControlActive = mouseControlExpected;
					}
					else
					{
						wasMouseControlActive = false;
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_MoveUp))
					{
						Features::FreeCamera::Move(0.0f, 0.0f, Features::FreeCamera::cameraMovementStep);
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_MoveDown))
					{
						Features::FreeCamera::Move(0.0f, 0.0f, Features::FreeCamera::cameraMovementStep * -1.0f);
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_MoveForward))
					{
						Features::FreeCamera::Move(Features::FreeCamera::cameraMovementStep, 0.0f, 0.0f);
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_MoveBackward))
					{
						Features::FreeCamera::Move(Features::FreeCamera::cameraMovementStep * -1.0f, 0.0f, 0.0f);
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_MoveLeft))
					{
						Features::FreeCamera::Move(0.0f, Features::FreeCamera::cameraMovementStep * -1.0f, 0.0f);
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_MoveRight))
					{
						Features::FreeCamera::Move(0.0f, Features::FreeCamera::cameraMovementStep, 0.0f);
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_RotateUp))
					{
						Features::FreeCamera::Rotate(0.0f, Features::FreeCamera::cameraRotationStep);
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_RotateDown))
					{
						Features::FreeCamera::Rotate(0.0f, Features::FreeCamera::cameraRotationStep * -1.0f);
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_RotateLeft))
					{
						Features::FreeCamera::Rotate(Features::FreeCamera::cameraRotationStep * -1.0f, 0.0f);
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_RotateRight))
					{
						Features::FreeCamera::Rotate(Features::FreeCamera::cameraRotationStep, 0.0f);
					}
				}
			}
		}

		Sleep(Math::Seconds_ToMilliseconds(delay));
	}
}


void BackgroundTasks::KeybindingsHandler::Enable()
{
	if (thread == nullptr)
	{
		thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)BackgroundTasks::KeybindingsHandler::Worker, 0, 0, 0);
		isEnabled = thread;
	}
}

void BackgroundTasks::KeybindingsHandler::Disable()
{
	if (thread)
	{
		isEnabled = false;

		WaitForSingleObject(thread, INFINITE);
		CloseHandle(thread);

		thread = nullptr;
	}
}


void BackgroundTasks::DirectionalMovementHandler::Worker()
{
	while (isEnabled)
	{
		bool allowMovement = Features::DirectionalMovement::enabled;

		allowMovement = allowMovement && Features::FreeCamera::IsEnabled() == false;

		if (allowMovement)
		{
			__try
			{
				/* See if we have a Player Controller alongside the Camera Manager. */
				SDK::APlayerController* playerController = Unreal::PlayerController::Get();
				if (playerController && playerController->PlayerCameraManager)
				{
					/* See if we have a Character under control and verify that Character is cheat flying. */
					SDK::ACharacter* character = playerController->Character;
					if (character && character->CharacterMovement && character->CharacterMovement->bCheatFlying)
					{
						bool movementExpected = false;
						SDK::FVector movementDirection = { 0.0f, 0.0f, 0.0f };

						if (Features::DirectionalMovement::omniMovement && Features::DirectionalMovement::independentOmniMovement)
						{
							SDK::FVector cameraForwardVector = playerController->PlayerCameraManager->GetActorForwardVector();
							SDK::FVector cameraRightVector = playerController->PlayerCameraManager->GetActorRightVector();
							SDK::FVector characterUpVector = character->GetActorUpVector();

							if (Features::DirectionalMovement::isUpMovementExpected)
							{
								movementExpected = true;
								movementDirection = Math::Vector_Add(movementDirection, characterUpVector);
							}

							if (Features::DirectionalMovement::isDownMovementExpected)
							{
								movementExpected = true;
								movementDirection = Math::Vector_Add(movementDirection, characterUpVector * -1.0f);
							}

							if (Features::DirectionalMovement::isForwardMovementExpected)
							{
								movementExpected = true;
								movementDirection = Math::Vector_Add(movementDirection, cameraForwardVector);
							}

							if (Features::DirectionalMovement::isBackwardMovementExpected)
							{
								movementExpected = true;
								movementDirection = Math::Vector_Add(movementDirection, cameraForwardVector * -1.0f);
							}

							if (Features::DirectionalMovement::isLeftMovementExpected)
							{
								movementExpected = true;
								movementDirection = Math::Vector_Add(movementDirection, cameraRightVector * -1.0f);
							}

							if (Features::DirectionalMovement::isRightMovementExpected)
							{
								movementExpected = true;
								movementDirection = Math::Vector_Add(movementDirection, cameraRightVector);
							}
						}
						else
						{
							/* Get Character velocity and see if we have any horizontal movement. */
							SDK::FVector characterVelocity = character->CharacterMovement->Velocity;
							bool hasHorizontalVelocity = (characterVelocity.X != 0.0 || characterVelocity.Y != 0.0);

							if (hasHorizontalVelocity || Features::DirectionalMovement::omniMovement)
							{
								/* Normalize Character velocity (-1.0 to 1.0) and get Camera forward vector. */
								SDK::FVector characterVelocityNormalized = Math::Vector_Normal(characterVelocity);
								SDK::FVector cameraForwardVector = playerController->PlayerCameraManager->GetActorForwardVector();

								/*
									Compute the dot product of the normalized character velocity and the camera's forward vector.
									Result interpretation:
									  +1.0 -> character moves exactly forward,
									  -1.0 -> character moves exactly backward,
									   0.0 -> movement is perpendicular to the camera.
								*/
								double dotForward = Math::Vector_Dot(characterVelocityNormalized, cameraForwardVector);
								if (dotForward > 0.5f) // Check if Ñharacter is attempting to move forward relative to the camera.
								{
									movementExpected = true;
									movementDirection = cameraForwardVector;
								}

								/* Handle multi-directional movement (Backward, Left, Right) if Omni-Movement is enabled. */
								if (Features::DirectionalMovement::omniMovement)
								{
									if (movementExpected == false && dotForward < -0.5f) // Check for backward movement (dot product is negative) if not already moving forward.
									{
										movementExpected = true;
										movementDirection = cameraForwardVector * -1.0f;
									}

									/* Retrieve the Camera right vector to calculate strafing. */
									SDK::FVector cameraRightVector = playerController->PlayerCameraManager->GetActorRightVector();
									double dotRight = Math::Vector_Dot(characterVelocityNormalized, cameraRightVector);

									if (dotRight > 0.5f) // Check if Character is strafing right.
									{
										movementExpected = true;
										movementDirection = Math::Vector_Add(movementDirection, cameraRightVector);
									}
									else if (dotRight < -0.5f) // Check if Character is strafing left
									{
										movementExpected = true;
										movementDirection = Math::Vector_Add(movementDirection, cameraRightVector * -1.0f);
									}

									if (Features::DirectionalMovement::isUpMovementExpected || Features::DirectionalMovement::isDownMovementExpected)
									{
										SDK::FVector characterUpVector = character->GetActorUpVector();
										if (Features::DirectionalMovement::isUpMovementExpected)
										{
											movementExpected = true;
											movementDirection = Math::Vector_Add(movementDirection, characterUpVector);
										}
										else if (Features::DirectionalMovement::isDownMovementExpected)
										{
											movementExpected = true;
											movementDirection = Math::Vector_Add(movementDirection, characterUpVector * -1.0f);
										}
									}
								}
							}
						}

						if (movementExpected)
						{
							/* Normalize the final accumulated direction vector to ensure consistent speed (account for forward/backward and strafing movement double speed). */
							SDK::FVector finalDirection = Math::Vector_Normal(movementDirection);

							/* Calculate the target location based on the current location, direction, and step size. */
							SDK::FVector currentLocation = Unreal::Actor::GetLocation(character);
							SDK::FVector finalLocation = Math::Vector_Add(currentLocation, finalDirection * Features::DirectionalMovement::step);

							Unreal::Actor::SweepTo(character, finalLocation);
						}
					}
				}
			}
			__except (EXCEPTION()) {}
		}

		/* Sleep for a defined delay to control the update rate (tick) of the movement logic. */
		Sleep(Math::Seconds_ToMilliseconds(delay));
	}
}


void BackgroundTasks::DirectionalMovementHandler::Enable()
{
	if (thread == nullptr)
	{
		thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)BackgroundTasks::DirectionalMovementHandler::Worker, 0, 0, 0);
		isEnabled = thread;
	}
}

void BackgroundTasks::DirectionalMovementHandler::Disable()
{
	if (thread)
	{
		isEnabled = false;

		WaitForSingleObject(thread, INFINITE);
		CloseHandle(thread);

		thread = nullptr;
	}
}


#ifdef TASK_CONSTRUCT_CONSOLE
void BackgroundTasks::ConstructConsole::Worker()
{
	while (isEnabled)
	{
		if (consoleConstructed == false)
		{
			if (Unreal::Console::Get())
				consoleConstructed = true;
			else
				consoleConstructed = Unreal::Console::Construct();
		}

		if (consoleConstructed && consoleBindingsAssigned == false)
			consoleBindingsAssigned = Unreal::InputSettings::AssignConsoleBindings();

		Sleep(Math::Seconds_ToMilliseconds(delay));
	}
}

void BackgroundTasks::ConstructConsole::Enable()
{
	if (thread == nullptr)
	{
		thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)BackgroundTasks::ConstructConsole::Worker, 0, 0, 0);
		isEnabled = thread;
	}
}

void BackgroundTasks::ConstructConsole::Disable()
{
	if (thread)
	{
		isEnabled = false;

		WaitForSingleObject(thread, INFINITE);
		CloseHandle(thread);

		thread = nullptr;
	}
}
#endif


#ifdef TASK_CONSTRUCT_CHEATMANAGER
void BackgroundTasks::ConstructCheatManager::Worker()
{
	while (thread)
	{
		if (cheatManagerConstructed == false)
		{
			if (Unreal::CheatManager::Get())
				cheatManagerConstructed = true;
			else
				cheatManagerConstructed = Unreal::CheatManager::Construct();
		}

		Sleep(Math::Seconds_ToMilliseconds(delay));
	}
}

void BackgroundTasks::ConstructCheatManager::Enable()
{
	if (thread == nullptr)
	{
		thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)BackgroundTasks::ConstructCheatManager::Worker, 0, 0, 0);
		isEnabled = thread;
	}
}

void BackgroundTasks::ConstructCheatManager::Disable()
{
	if (thread)
	{
		isEnabled = false;

		WaitForSingleObject(thread, INFINITE);
		CloseHandle(thread);

		thread = nullptr;
	}
}
#endif


void BackgroundTasks::Init()
{
	BackgroundTasks::KeybindingsHandler::Enable();

	BackgroundTasks::DirectionalMovementHandler::Enable();

#ifdef TASK_CONSTRUCT_CONSOLE
	BackgroundTasks::ConstructConsole::Enable();
#endif

#ifdef TASK_CONSTRUCT_CHEATMANAGER
	BackgroundTasks::ConstructCheatManager::Enable();
#endif
}






// ==============================
// |          #Inputs			|
// ==============================
void Inputs::Config::ReadKeyBindingFromConfig(ConfigInstance* keybindingsConfig, const std::string& entryName, ImGui::KeyBinding* keyBinding)
{
	if (keybindingsConfig == nullptr || keyBinding == nullptr)
		return;

	if (keybindingsConfig->HasKey(entryName) == false)
		return;

	keyBinding->key = static_cast<ImGuiKey>(keybindingsConfig->GetKey<int>(entryName).value_or((int)keyBinding->key));
}

void Inputs::Config::Load()
{
	ConfigInstance keybindingsConfig(PATH_CONFIG_KEYBINDINGS);
	if (keybindingsConfig.Load() == false)
	{
		Inputs::Config::Save();
		keybindingsConfig.Load();
	}

	ReadKeyBindingFromConfig(&keybindingsConfig, "general_MenuOpenClose", &Inputs::Keybindings::general_MenuOpenClose);

	ReadKeyBindingFromConfig(&keybindingsConfig, "debug_ActorTrace", &Inputs::Keybindings::debug_ActorTrace);

	ReadKeyBindingFromConfig(&keybindingsConfig, "debug_ActorsListUpdate", &Inputs::Keybindings::debug_ActorsListUpdate);

	ReadKeyBindingFromConfig(&keybindingsConfig, "debug_ActorsListTracking", &Inputs::Keybindings::debug_ActorsListTracking);

#ifdef COLLISION_VISUALIZER
	ReadKeyBindingFromConfig(&keybindingsConfig, "debug_ActorsListCollisionDraw", &Inputs::Keybindings::debug_ActorsListCollisionDraw);
#endif

	ReadKeyBindingFromConfig(&keybindingsConfig, "characterMovement_Ghost", &Inputs::Keybindings::characterMovement_Ghost);
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterMovement_Fly", &Inputs::Keybindings::characterMovement_Fly);
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterMovement_Walk", &Inputs::Keybindings::characterMovement_Walk);
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterMovement_Jump", &Inputs::Keybindings::characterMovement_Jump);
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterMovement_Launch", &Inputs::Keybindings::characterMovement_Launch);
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterMovement_Dash", &Inputs::Keybindings::characterMovement_Dash);

	ReadKeyBindingFromConfig(&keybindingsConfig, "characterOmniMovement_Up", &Inputs::Keybindings::characterOmniMovement_Up);
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterOmniMovement_Down", &Inputs::Keybindings::characterOmniMovement_Down);
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterOmniMovement_Forward", &Inputs::Keybindings::characterOmniMovement_Forward);
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterOmniMovement_Backward", &Inputs::Keybindings::characterOmniMovement_Backward);
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterOmniMovement_Left", &Inputs::Keybindings::characterOmniMovement_Left);
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterOmniMovement_Right", &Inputs::Keybindings::characterOmniMovement_Right);
	
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterCamera_StartFade", &Inputs::Keybindings::characterCamera_StartFade);
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterCamera_StopFade", &Inputs::Keybindings::characterCamera_StopFade);

	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_Toggle", &Inputs::Keybindings::freeCamera_Toggle);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_TeleportPlayerToCamera", &Inputs::Keybindings::freeCamera_TeleportPlayerToCamera);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_TeleportCameraToPlayer", &Inputs::Keybindings::freeCamera_TeleportCameraToPlayer);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_MoveUp", &Inputs::Keybindings::freeCamera_MoveUp);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_MoveDown", &Inputs::Keybindings::freeCamera_MoveDown);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_MoveForward", &Inputs::Keybindings::freeCamera_MoveForward);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_MoveBackward", &Inputs::Keybindings::freeCamera_MoveBackward);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_MoveLeft", &Inputs::Keybindings::freeCamera_MoveLeft);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_MoveRight", &Inputs::Keybindings::freeCamera_MoveRight);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_RotateUp", &Inputs::Keybindings::freeCamera_RotateUp);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_RotateDown", &Inputs::Keybindings::freeCamera_RotateDown);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_RotateLeft", &Inputs::Keybindings::freeCamera_RotateLeft);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_RotateRight", &Inputs::Keybindings::freeCamera_RotateRight);
}

void Inputs::Config::Save()
{
	ConfigInstance keybindingsConfig(PATH_CONFIG_KEYBINDINGS);
	
	keybindingsConfig.SetKey("general_MenuOpenClose", static_cast<int>(Inputs::Keybindings::general_MenuOpenClose.key));

	keybindingsConfig.SetKey("debug_ActorTrace", static_cast<int>(Keybindings::debug_ActorTrace.key));

	keybindingsConfig.SetKey("debug_ActorsListUpdate", static_cast<int>(Inputs::Keybindings::debug_ActorsListUpdate.key));

	keybindingsConfig.SetKey("debug_ActorsListTracking", static_cast<int>(Keybindings::debug_ActorsListTracking.key));

#ifdef COLLISION_VISUALIZER
	keybindingsConfig.SetKey("debug_ActorsListCollisionDraw", static_cast<int>(Keybindings::debug_ActorsListCollisionDraw.key));
#endif

	keybindingsConfig.SetKey("characterMovement_Ghost", static_cast<int>(Inputs::Keybindings::characterMovement_Ghost.key));
	keybindingsConfig.SetKey("characterMovement_Fly", static_cast<int>(Inputs::Keybindings::characterMovement_Fly.key));
	keybindingsConfig.SetKey("characterMovement_Walk", static_cast<int>(Inputs::Keybindings::characterMovement_Walk.key));
	keybindingsConfig.SetKey("characterMovement_Jump", static_cast<int>(Inputs::Keybindings::characterMovement_Jump.key));
	keybindingsConfig.SetKey("characterMovement_Launch", static_cast<int>(Inputs::Keybindings::characterMovement_Launch.key));
	keybindingsConfig.SetKey("characterMovement_Dash", static_cast<int>(Inputs::Keybindings::characterMovement_Dash.key));

	keybindingsConfig.SetKey("characterOmniMovement_Up", static_cast<int>(Inputs::Keybindings::characterOmniMovement_Up.key));
	keybindingsConfig.SetKey("characterOmniMovement_Down", static_cast<int>(Inputs::Keybindings::characterOmniMovement_Down.key));
	keybindingsConfig.SetKey("characterOmniMovement_Forward", static_cast<int>(Inputs::Keybindings::characterOmniMovement_Forward.key));
	keybindingsConfig.SetKey("characterOmniMovement_Backward", static_cast<int>(Inputs::Keybindings::characterOmniMovement_Backward.key));
	keybindingsConfig.SetKey("characterOmniMovement_Left", static_cast<int>(Inputs::Keybindings::characterOmniMovement_Left.key));
	keybindingsConfig.SetKey("characterOmniMovement_Right", static_cast<int>(Inputs::Keybindings::characterOmniMovement_Right.key));

	keybindingsConfig.SetKey("characterCamera_StartFade", static_cast<int>(Inputs::Keybindings::characterCamera_StartFade.key));
	keybindingsConfig.SetKey("characterCamera_StopFade", static_cast<int>(Inputs::Keybindings::characterCamera_StopFade.key));

	keybindingsConfig.SetKey("freeCamera_Toggle", static_cast<int>(Keybindings::freeCamera_Toggle.key));
	keybindingsConfig.SetKey("freeCamera_TeleportPlayerToCamera", static_cast<int>(Keybindings::freeCamera_TeleportPlayerToCamera.key));
	keybindingsConfig.SetKey("freeCamera_TeleportCameraToPlayer", static_cast<int>(Keybindings::freeCamera_TeleportCameraToPlayer.key));
	keybindingsConfig.SetKey("freeCamera_MoveUp", static_cast<int>(Keybindings::freeCamera_MoveUp.key));
	keybindingsConfig.SetKey("freeCamera_MoveDown", static_cast<int>(Keybindings::freeCamera_MoveDown.key));
	keybindingsConfig.SetKey("freeCamera_MoveForward", static_cast<int>(Keybindings::freeCamera_MoveForward.key));
	keybindingsConfig.SetKey("freeCamera_MoveBackward", static_cast<int>(Keybindings::freeCamera_MoveBackward.key));
	keybindingsConfig.SetKey("freeCamera_MoveLeft", static_cast<int>(Keybindings::freeCamera_MoveLeft.key));
	keybindingsConfig.SetKey("freeCamera_MoveRight", static_cast<int>(Keybindings::freeCamera_MoveRight.key));
	keybindingsConfig.SetKey("freeCamera_RotateUp", static_cast<int>(Keybindings::freeCamera_RotateUp.key));
	keybindingsConfig.SetKey("freeCamera_RotateDown", static_cast<int>(Keybindings::freeCamera_RotateDown.key));
	keybindingsConfig.SetKey("freeCamera_RotateLeft", static_cast<int>(Keybindings::freeCamera_RotateLeft.key));
	keybindingsConfig.SetKey("freeCamera_RotateRight", static_cast<int>(Keybindings::freeCamera_RotateRight.key));

	keybindingsConfig.Save();
}






// ==============================
// |        #DebugDraw			|
// ==============================
#ifdef COLLISION_VISUALIZER
void DebugDraw::DrawBodySetup(SDK::UBodySetup* bodySetup, const Unreal::Transform& componentTransform, const uint32_t& drawColor, const float drawThickness)
{
	if (bodySetup == nullptr)
		return;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return;

	ImDrawList* drawList = ImGui::GetDrawList();
	if (drawList == nullptr)
		return;

	for (SDK::FKConvexElem& convexElement : bodySetup->AggGeom.ConvexElems)
	{
		const SDK::TArray<SDK::FVector>& vertexData = convexElement.VertexData;
		const size_t vertexDataLength = vertexData.Num();
		if (vertexDataLength == 0)
			continue;

		const SDK::TArray<int32_t>& indexData = convexElement.IndexData;
		const size_t indexDataLength = indexData.Num();
		if (indexDataLength < 3 || indexDataLength % 3 != 0)
			continue;

		for (int32_t i = 0; i + 2 < indexDataLength; i += 3)
		{
			int32_t A_Index = indexData[i];
			int32_t B_Index = indexData[i + 1];
			int32_t C_Index = indexData[i + 2];

			if (A_Index < 0 || A_Index >= vertexDataLength ||
				B_Index < 0 || B_Index >= vertexDataLength ||
				C_Index < 0 || C_Index >= vertexDataLength)
				continue;

			if (A_Index == B_Index || B_Index == C_Index || C_Index == A_Index)
				continue;

			SDK::FVector A_Local = vertexData[A_Index];
			SDK::FVector B_Local = vertexData[B_Index];
			SDK::FVector C_Local = vertexData[C_Index];

			SDK::FVector A_World = Math::Vector_LocalToWorld(componentTransform, A_Local);
			SDK::FVector B_World = Math::Vector_LocalToWorld(componentTransform, B_Local);
			SDK::FVector C_World = Math::Vector_LocalToWorld(componentTransform, C_Local);

			SDK::FVector2D A_Screen, B_Screen, C_Screen;
			bool A_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, A_World, &A_Screen, false);
			bool B_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, B_World, &B_Screen, false);
			bool C_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, C_World, &C_Screen, false);

			if (A_Project && B_Project && C_Project)
			{
				drawList->AddLine(ImVec2(A_Screen.X, A_Screen.Y), ImVec2(B_Screen.X, B_Screen.Y), drawColor, drawThickness);
				drawList->AddLine(ImVec2(B_Screen.X, B_Screen.Y), ImVec2(C_Screen.X, C_Screen.Y), drawColor, drawThickness);
				drawList->AddLine(ImVec2(C_Screen.X, C_Screen.Y), ImVec2(A_Screen.X, A_Screen.Y), drawColor, drawThickness);
			}
		}
	}
}

void DebugDraw::DrawVolume(SDK::AVolume* volume, const uint32_t& drawColor, const float drawThickness)
{
	if (volume == nullptr)
		return;

	if (volume->BrushComponent == nullptr)
		return;

	SDK::UBrushComponent* brushComponent = volume->BrushComponent;
	if (brushComponent->BrushBodySetup == nullptr)
		return;

	SDK::UBodySetup* bodySetup = brushComponent->BrushBodySetup;
	Unreal::Transform componentTransform = Unreal::ActorComponent::GetTransform(brushComponent);

	DrawBodySetup(bodySetup, componentTransform, drawColor, drawThickness);
}




void DebugDraw::DrawStaticMeshComponent(SDK::UStaticMeshComponent* staticMeshComponent, const uint32_t& drawColor, const float drawThickness)
{
	if (staticMeshComponent == nullptr)
		return;

	if (staticMeshComponent->StaticMesh == nullptr)
		return;

	SDK::UStaticMesh* staticMesh = static_cast<SDK::UStaticMesh*>(staticMeshComponent->StaticMesh);
	if (staticMesh->BodySetup == nullptr)
		return;

	SDK::UBodySetup* bodySetup = staticMesh->BodySetup;
	Unreal::Transform componentTransform = Unreal::ActorComponent::GetTransform(staticMeshComponent);

	DrawBodySetup(bodySetup, componentTransform, drawColor, drawThickness);
}

void DebugDraw::DrawInstancedStaticMeshComponent(SDK::UInstancedStaticMeshComponent* instancedStaticMeshComponent, const uint32_t& drawColor, const float drawThickness)
{
	if (instancedStaticMeshComponent == nullptr)
		return;

	if (instancedStaticMeshComponent->StaticMesh == nullptr)
		return;

	SDK::UStaticMesh* staticMesh = static_cast<SDK::UStaticMesh*>(instancedStaticMeshComponent->StaticMesh);
	if (staticMesh->BodySetup == nullptr)
		return;

	SDK::UBodySetup* bodySetup = staticMesh->BodySetup;
	Unreal::Transform componentTransform = Unreal::ActorComponent::GetTransform(instancedStaticMeshComponent);

	DrawBodySetup(bodySetup, componentTransform, drawColor, drawThickness);
}




void DebugDraw::DrawSkeletalMeshComponent(SDK::USkeletalMeshComponent* skeletalMeshComponent, bool drawAllSockets, const uint32_t& drawColor, const float drawThickness)
{
	if (skeletalMeshComponent == nullptr)
		return;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return;

	ImDrawList* drawList = ImGui::GetDrawList();
	if (drawList == nullptr)
		return;

	static const std::vector<std::string> commonBoneNames =
	{
		"root", "pelvis", "spine", "neck", "head",
		"hand", "foot", "calf", "thigh", "arm",
		"clavicle", "joint"
	};

	std::vector<SDK::FName> socketNamesToDraw;
	std::vector<SDK::FName> spottedBonesNames;
	SDK::TArray<SDK::FName> socketNamesCollection = skeletalMeshComponent->GetAllSocketNames();
	for (SDK::FName socketName : socketNamesCollection)
	{
		SDK::FName boneName = skeletalMeshComponent->GetSocketBoneName(socketName);

		bool isUniqueBone = true;
		for (SDK::FName spottedBoneName : spottedBonesNames)
		{
			if (boneName == spottedBoneName)
				isUniqueBone = false;
		}

		if (isUniqueBone == false)
			continue;


		if (drawAllSockets == false)
		{
			bool isCommonBone = false;
			for (std::string commonBoneName : commonBoneNames)
			{
				std::string sBoneName = boneName.ToString();
				if (Utilities::String::ToLowerCase(sBoneName).find(commonBoneName) != std::string::npos)
					isCommonBone = true;
			}

			if (isCommonBone == false)
				continue;
		}


		spottedBonesNames.push_back(boneName);
		socketNamesToDraw.push_back(socketName);
	}

	for (SDK::FName socketName : socketNamesToDraw)
	{
		/* GetSocketLocation() returns world location out of the box. */
		SDK::FVector socket_World = skeletalMeshComponent->GetSocketLocation(socketName);

		SDK::FVector2D socket_Screen;
		if (SDK::UGameplayStatics::ProjectWorldToScreen(playerController, socket_World, &socket_Screen, false))
		{
			drawList->AddCircleFilled(ImVec2(socket_Screen.X, socket_Screen.Y), drawThickness * 2, drawColor);
		}
	}
}




void DebugDraw::DrawCapsuleComponent(SDK::UCapsuleComponent* capsuleComponent, const uint32_t& drawColor, const float drawThickness)
{
	if (capsuleComponent == nullptr)
		return;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return;

	ImDrawList* drawList = ImGui::GetDrawList();
	if (drawList == nullptr)
		return;

	float capsuleRadius = capsuleComponent->GetScaledCapsuleRadius();
	float capsuleHalfHeight = capsuleComponent->GetScaledCapsuleHalfHeight();

	Unreal::Transform capsuleTransform = Unreal::ActorComponent::GetTransform(capsuleComponent);
	SDK::FVector capsuleUpVector = Math::Rotator_UpVector(capsuleTransform.rotation);

	/* Construct an orthonormal basis (axis, U, V) for building capsule rings. */
	SDK::FVector ortho_Temp = (fabsf(capsuleUpVector.Z) < 0.99f) ? SDK::FVector(0.f, 0.f, 1.f) : SDK::FVector(0.f, 1.f, 0.f); // Choose a temporary vector that is not parallel to the capsule axis.
	SDK::FVector ortho_U = Math::Vector_Normal(Math::Vector_Cross(capsuleUpVector, ortho_Temp), 0.01f); // Compute 'U' as a normalized vector perpendicular to 'axis'.
	SDK::FVector ortho_V = Math::Vector_Normal(Math::Vector_Cross(capsuleUpVector, ortho_U), 0.01f); // Compute 'V' as a normalized vector perpendicular to both 'axis' and 'U'.

	/* True top/bottom endpoints of the capsule (tips). */
	const SDK::FVector capsuleTopTip = capsuleTransform.location + capsuleUpVector * capsuleHalfHeight;
	const SDK::FVector capsuleBottomTip = capsuleTransform.location - capsuleUpVector * capsuleHalfHeight;

	/* Centers of the hemispherical caps. These are located radius units away from the tips toward the middle. */
	const SDK::FVector sphereTopCenter = capsuleTransform.location + capsuleUpVector * (capsuleHalfHeight - capsuleRadius);
	const SDK::FVector sphereBottomCenter = capsuleTransform.location - capsuleUpVector * (capsuleHalfHeight - capsuleRadius);

	/* Project tips to optionally use for hemisphere polylines. */
	SDK::FVector2D capsuleTopTip_Screen, capsuleBottomTip_Screen;
	bool capsuleTopTip_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, capsuleTopTip, &capsuleTopTip_Screen, false);
	bool capsuleBottomTip_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, capsuleBottomTip, &capsuleBottomTip_Screen, false);

	static int32_t capsuleSegments = 24;
	static int32_t hemisphereSegments = 6; // Number of segments from tip to seam to approximate the spherical rounding.
	for (int32_t i = 0; i < capsuleSegments; i++)
	{
		/*
			A ----------> B

			A - Current ring angle (azimuth).
			B - Next ring angle (azimuth).
		*/

		/* Compute the start (ringA_Angle) and end (ringB_Angle) angles for the current ring segment in radians. */
		const float ringA_Angle = (2.0f * Math::PI) * (float)i / (float)capsuleSegments;
		const float ringB_Angle = (2.0f * Math::PI) * (float)(i + 1) / (float)capsuleSegments;

		/* Unit directions around the capsule axis for current and next azimuths. */
		const SDK::FVector unitDirectionA = ortho_U * cosf(ringA_Angle) + ortho_V * sinf(ringA_Angle);
		const SDK::FVector unitDirectionB = ortho_U * cosf(ringB_Angle) + ortho_V * sinf(ringB_Angle);

		/* Rings at the cylinder/hemisphere seam (equators of the spherical caps). */
		SDK::FVector ringA_Top = sphereTopCenter + unitDirectionA * capsuleRadius;
		SDK::FVector ringB_Top = sphereTopCenter + unitDirectionB * capsuleRadius;
		SDK::FVector ringA_Bottom = sphereBottomCenter + unitDirectionA * capsuleRadius;
		SDK::FVector ringB_Bottom = sphereBottomCenter + unitDirectionB * capsuleRadius;

		SDK::FVector2D ringA_Top_Screen, ringB_Top_Screen, ringA_Bottom_Screen, ringB_Bottom_Screen;
		bool ringA_Top_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, ringA_Top, &ringA_Top_Screen, false);
		bool ringB_Top_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, ringB_Top, &ringB_Top_Screen, false);
		bool ringA_Bottom_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, ringA_Bottom, &ringA_Bottom_Screen, false);
		bool ringB_Bottom_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, ringB_Bottom, &ringB_Bottom_Screen, false);

		/* Outlines the top seam ring. */
		if (ringA_Top_Project && ringB_Top_Project)
			drawList->AddLine(ImVec2(ringA_Top_Screen.X, ringA_Top_Screen.Y), ImVec2(ringB_Top_Screen.X, ringB_Top_Screen.Y), drawColor, drawThickness);

		/* Outlines the bottom seam ring. */
		if (ringA_Bottom_Project && ringB_Bottom_Project)
			drawList->AddLine(ImVec2(ringA_Bottom_Screen.X, ringA_Bottom_Screen.Y), ImVec2(ringB_Bottom_Screen.X, ringB_Bottom_Screen.Y), drawColor, drawThickness);

		/* Outlines side walls (cylindrical part). */
		if (ringA_Top_Project && ringA_Bottom_Project)
			drawList->AddLine(ImVec2(ringA_Top_Screen.X, ringA_Top_Screen.Y), ImVec2(ringA_Bottom_Screen.X, ringA_Bottom_Screen.Y), drawColor, drawThickness);

		/* Draw spherical rounding for top and bottom by tracing meridian polylines from tip to seam. */
		for (int32_t segment = 0; segment < hemisphereSegments; ++segment)
		{
			/*
				phi goes from 0 (tip) to PI/2 (seam). We connect successive samples to approximate a meridian.
				Top hemisphere position (for azimuth dirA): P(phi) = sphereTopCenter + capsuleRadius * ( dirA * sin(phi) + capsuleUpVector * cos(phi) )
				Bottom hemisphere: P(phi) = sphereBottomCenter + capsuleRadius * ( dirA * sin(phi) - capsuleUpVector * cos(phi) )
			*/
			float phi0 = (Math::PI * 0.5f) * (float)segment / (float)hemisphereSegments;
			float phi1 = (Math::PI * 0.5f) * (float)(segment + 1) / (float)hemisphereSegments;

			SDK::FVector pointA_Top = sphereTopCenter + (unitDirectionA * sinf(phi0) + capsuleUpVector * cosf(phi0)) * capsuleRadius;
			SDK::FVector pointB_Top = sphereTopCenter + (unitDirectionA * sinf(phi1) + capsuleUpVector * cosf(phi1)) * capsuleRadius;

			SDK::FVector pointA_Bottom = sphereBottomCenter + (unitDirectionA * sinf(phi0) - capsuleUpVector * cosf(phi0)) * capsuleRadius;
			SDK::FVector pointB_Bottom = sphereBottomCenter + (unitDirectionA * sinf(phi1) - capsuleUpVector * cosf(phi1)) * capsuleRadius;

			SDK::FVector2D PointA_Top_Screen, PointB_Top_Screen, PointA_Bottom_Screen, PointB_Bottom_Screen;
			bool pointA_Top_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, pointA_Top, &PointA_Top_Screen, false);
			bool pointB_Top_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, pointB_Top, &PointB_Top_Screen, false);
			bool pointA_Bottom_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, pointA_Bottom, &PointA_Bottom_Screen, false);
			bool pointB_Bottom_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, pointB_Bottom, &PointB_Bottom_Screen, false);

			if (pointA_Top_Project && pointB_Top_Project)
				drawList->AddLine(ImVec2(PointA_Top_Screen.X, PointA_Top_Screen.Y), ImVec2(PointB_Top_Screen.X, PointB_Top_Screen.Y), drawColor, drawThickness);

			if (pointA_Bottom_Project && pointB_Bottom_Project)
				drawList->AddLine(ImVec2(PointA_Bottom_Screen.X, PointA_Bottom_Screen.Y), ImVec2(PointB_Bottom_Screen.X, PointB_Bottom_Screen.Y), drawColor, drawThickness);
		}
	}
}


void DebugDraw::DrawSphereComponent(SDK::USphereComponent* sphereComponent, const uint32_t& drawColor, const float drawThickness)
{
	if (sphereComponent == nullptr)
		return;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return;

	ImDrawList* drawList = ImGui::GetDrawList();
	if (drawList == nullptr)
		return;

	/* Get sphere data. */
	float sphereRadius = sphereComponent->GetScaledSphereRadius();
	Unreal::Transform sphereTransform = Unreal::ActorComponent::GetTransform(sphereComponent);
	SDK::FVector sphereCenter = sphereTransform.location;

	/* Build local orthonormal frame from component rotation. */
	SDK::FVector sphereForwardVector = Math::Rotator_ForwardVector(sphereTransform.rotation);
	SDK::FVector sphereRightVector = Math::Rotator_RightVector(sphereTransform.rotation);
	SDK::FVector sphereUpVector = Math::Rotator_UpVector(sphereTransform.rotation);

	/* Determine level of detail for volume. */
	static int32_t numMeridians = 6; // Number of vertical rings (from pole to pole).
	static int32_t numParallels = 4; // Number of horizontal rings (latitudes).
	static int32_t sphereSegments = 32;

	/* Draw Meridians (great circles passing through the poles). */
	for (int32_t i = 0; i < numMeridians; ++i)
	{
		float angle = Math::PI * (float)i / (float)numMeridians;

		/* Create basis for the current meridian. */
		SDK::FVector U = sphereRightVector * cosf(angle) + sphereForwardVector * sinf(angle);
		SDK::FVector V = sphereUpVector;

		for (int32_t segment = 0; segment < sphereSegments; ++segment)
		{
			/* Parametric angles for current and next segment. */
			float angleA = (2.0f * Math::PI) * (float)segment / (float)sphereSegments;
			float angleB = (2.0f * Math::PI) * (float)(segment + 1) / (float)sphereSegments;

			/* Points on the ring in world space. */
			SDK::FVector pointA = sphereCenter + (U * cosf(angleA) + V * sinf(angleA)) * sphereRadius;
			SDK::FVector pointB = sphereCenter + (U * cosf(angleB) + V * sinf(angleB)) * sphereRadius;

			/* Project and draw segment if visible. */
			SDK::FVector2D pointA_Screen, pointB_Screen;
			bool pointA_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, pointA, &pointA_Screen, false);
			bool pointB_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, pointB, &pointB_Screen, false);

			if (pointA_Project && pointB_Project)
				drawList->AddLine(ImVec2(pointA_Screen.X, pointA_Screen.Y), ImVec2(pointB_Screen.X, pointB_Screen.Y), drawColor, drawThickness);
		}
	}

	/* Draw Parallels (horizontal rings at different heights). */
	for (int32_t i = 1; i < numParallels; ++i)
	{
		float phi = Math::PI * (float)i / (float)numParallels;
		float zOffset = cosf(phi) * sphereRadius;
		float currentRadius = sinf(phi) * sphereRadius;

		SDK::FVector planeCenter = sphereCenter + sphereUpVector * zOffset;

		/* Basis for parallels matches the equatorial plane. */
		SDK::FVector U = sphereRightVector;
		SDK::FVector V = sphereForwardVector;

		for (int32_t segment = 0; segment < sphereSegments; ++segment)
		{
			/* Parametric angles for current and next segment. */
			float angleA = (2.0f * Math::PI) * (float)segment / (float)sphereSegments;
			float angleB = (2.0f * Math::PI) * (float)(segment + 1) / (float)sphereSegments;

			/* Points on the ring in world space. */
			SDK::FVector pointA = planeCenter + (U * cosf(angleA) + V * sinf(angleA)) * currentRadius;
			SDK::FVector pointB = planeCenter + (U * cosf(angleB) + V * sinf(angleB)) * currentRadius;

			/* Project and draw segment if visible. */
			SDK::FVector2D pointA_Screen, pointB_Screen;
			bool pointA_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, pointA, &pointA_Screen, false);
			bool pointB_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, pointB, &pointB_Screen, false);

			if (pointA_Project && pointB_Project)
				drawList->AddLine(ImVec2(pointA_Screen.X, pointA_Screen.Y), ImVec2(pointB_Screen.X, pointB_Screen.Y), drawColor, drawThickness);
		}
	}
}

void DebugDraw::DrawBoxComponent(SDK::UBoxComponent* boxComponent, const uint32_t& drawColor, const float drawThickness)
{
	if (boxComponent == nullptr)
		return;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return;

	ImDrawList* drawList = ImGui::GetDrawList();
	if (drawList == nullptr)
		return;

	/* Get box transform and half extents in world units. */
	Unreal::Transform boxTransform = Unreal::ActorComponent::GetTransform(boxComponent);
	SDK::FVector boxLocation = boxTransform.location;
	SDK::FVector boxExtent = boxComponent->GetScaledBoxExtent();

	/* Local basis vectors from rotation (orthonormal). */
	SDK::FVector boxForwardVector = Math::Rotator_ForwardVector(boxTransform.rotation);
	SDK::FVector boxRightVector = Math::Rotator_RightVector(boxTransform.rotation);
	SDK::FVector boxUpVector = Math::Rotator_UpVector(boxTransform.rotation);

	/* Precompute axis-length vectors. */
	SDK::FVector boxForwardExtent = boxForwardVector * boxExtent.X;
	SDK::FVector boxRightExtent = boxRightVector * boxExtent.Y;
	SDK::FVector boxUpExtent = boxUpVector * boxExtent.Z;

	/* Compute the 8 corners of the oriented box. Indexing convention: XYZ, where X/Y/Z in {0, 1} mean -/+ along UpExtent/RightExtent/ForwardExtent. */
	SDK::FVector boxCorners_Location[8];
	boxCorners_Location[0] = boxLocation - boxForwardExtent - boxRightExtent - boxUpExtent; // c000
	boxCorners_Location[1] = boxLocation - boxForwardExtent - boxRightExtent + boxUpExtent; // c001
	boxCorners_Location[2] = boxLocation - boxForwardExtent + boxRightExtent - boxUpExtent; // c010
	boxCorners_Location[3] = boxLocation - boxForwardExtent + boxRightExtent + boxUpExtent; // c011
	boxCorners_Location[4] = boxLocation + boxForwardExtent - boxRightExtent - boxUpExtent; // c100
	boxCorners_Location[5] = boxLocation + boxForwardExtent - boxRightExtent + boxUpExtent; // c101
	boxCorners_Location[6] = boxLocation + boxForwardExtent + boxRightExtent - boxUpExtent; // c110
	boxCorners_Location[7] = boxLocation + boxForwardExtent + boxRightExtent + boxUpExtent; // c111

	/* Project all corners once. */
	SDK::FVector2D boxCorners_Screen[8];
	bool boxCorners_Project[8];
	for (int32_t i = 0; i < 8; ++i)
		boxCorners_Project[i] = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, boxCorners_Location[i], &boxCorners_Screen[i], false);

	/* Box edges as index pairs (12 edges). */
	static int32_t boxEdges[12][2] = {
		{0,1}, {0,2}, {0,4}, // from c000
		{7,3}, {7,5}, {7,6}, // from c111
		{1,3}, {1,5},        // edges on -F face
		{2,3}, {2,6},        // edges on +R face
		{4,5}, {4,6}         // edges on +F / -R faces
	};

	for (int32_t edge = 0; edge < 12; ++edge)
	{
		int32_t i0 = boxEdges[edge][0];
		int32_t i1 = boxEdges[edge][1];
		if (boxCorners_Project[i0] && boxCorners_Project[i1])
		{
			SDK::FVector2D p0 = boxCorners_Screen[i0];
			SDK::FVector2D p1 = boxCorners_Screen[i1];
			drawList->AddLine(ImVec2(p0.X, p0.Y), ImVec2(p1.X, p1.Y), drawColor, drawThickness);
		}
	}
}

void DebugDraw::DrawSplineComponent(SDK::USplineComponent* splineComponent, const uint32_t& drawColor, const float drawThickness)
{
	if (splineComponent == nullptr)
		return;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return;

	ImDrawList* drawList = ImGui::GetDrawList();
	if (drawList == nullptr)
		return;

	/* Get spline data. */
	int32_t splinePointsCount = splineComponent->GetNumberOfSplinePoints();
	if (splinePointsCount < 2)
		return;

	/* Get spline world transform. */
	Unreal::Transform splineTransform = Unreal::ActorComponent::GetTransform(splineComponent);

	/* Number of segments per spline section for smoothness. */
	static int32_t splineSegments = 16;
	for (int32_t pointIndex = 0; pointIndex < splinePointsCount - 1; ++pointIndex)
	{
		/* Get distances along the spline for this segment. */
		float segmentStartDistance = splineComponent->GetDistanceAlongSplineAtSplinePoint(pointIndex);
		float segmentEndDistance = splineComponent->GetDistanceAlongSplineAtSplinePoint(pointIndex + 1);
		float segmentLength = segmentEndDistance - segmentStartDistance;

		/* Subdivide spline segment for a smooth visual curve. */
		for (int32_t segment = 0; segment < splineSegments; ++segment)
		{
			float tA = (float)segment / (float)splineSegments;
			float tB = (float)(segment + 1) / (float)splineSegments;

			float distanceA = segmentStartDistance + tA * segmentLength;
			float distanceB = segmentStartDistance + tB * segmentLength;

			/* Get world-space positions along the spline. */
			SDK::FVector pointA = splineComponent->GetLocationAtDistanceAlongSpline(distanceA, SDK::ESplineCoordinateSpace::World);
			SDK::FVector pointB = splineComponent->GetLocationAtDistanceAlongSpline(distanceB, SDK::ESplineCoordinateSpace::World);

			/* Project and draw the segment if visible. */
			SDK::FVector2D pointA_Screen, pointB_Screen;
			bool pointA_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, pointA, &pointA_Screen, false);
			bool pointB_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, pointB, &pointB_Screen, false);

			if (pointA_Project && pointB_Project)
				drawList->AddLine(ImVec2(pointA_Screen.X, pointA_Screen.Y), ImVec2(pointB_Screen.X, pointB_Screen.Y), drawColor, drawThickness);
		}
	}
}
#endif






// ==============================
// |        #Templates			|
// ==============================
void Templates::ClassHierarchy::Draw(const std::vector<std::string>& superClassesNames)
{
	for (const std::string& className : superClassesNames)
	{
		ImGui::TextCopyable(("- " + className).c_str());
	}
}




void Templates::Functions::Draw(SDK::UObject* objectReference)
{
	ImGui::TitleText("Functions");
	if (ImGui::TreeNode("Details##Functions"))
	{
		if (ImGui::Button("Update##Functions"))
		{
			Features::Functions::functions = Unreal::Function::GetFunctions(objectReference);
			Features::Functions::functionsOwner = objectReference;
			GUI::PlayActionSound(true);
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		ImGui::InputText("Search Filter##Functions", Features::Functions::filterBuffer, Features::Functions::filterBufferSize);
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		ImGui::Checkbox("Case Sensitive##Functions", &Features::Functions::filterCaseSensitive);

		ImGui::NewLine();

		if (objectReference == Features::Functions::functionsOwner)
		{
			std::vector<Unreal::Function::DataStructure> filteredFunctions = Unreal::Function::FilterByName(Features::Functions::functions, Features::Functions::filterBuffer, Features::Functions::filterCaseSensitive);
			for (const Unreal::Function::DataStructure& function : filteredFunctions)
			{
				std::string memoryAddress = function.MemoryAddressAsString();
				ImGui::PushID(memoryAddress.c_str());

				if (ImGui::TreeNode(function.name.c_str()))
				{
					ImGui::TextCopyable("Flags: %s", function.FlagsAsString().c_str());
					ImGui::TextCopyable("Address: %s", memoryAddress.c_str());
					
					ImGui::NewLine();

					if (ImGui::Button("Call"))
					{
						bool wasSuccessful = Unreal::Function::CallFunction_ThreadSafe(objectReference, function.reference);
						GUI::PlayActionSound(wasSuccessful);
					}
					ImGui::TreePop();
				}

				ImGui::PopID();
			}
		}

		ImGui::TreePop();
	}
}




void Templates::LocationRotationScale::Draw(SDK::AActor* actorReference)
{
	static SDK::AActor* locationSource = nullptr;
	static SDK::AActor* rotationSource = nullptr;
	static SDK::AActor* scaleSource = nullptr;

	static float userProvidedLocation[3];
	static float userProvidedRotation[3];
	static float userProvidedScale[3];


	static SDK::AActor* relativeLocationSource = nullptr;
	static SDK::AActor* relativeRotationSource = nullptr;
	static SDK::AActor* relativeScaleSource = nullptr;

	static float userProvidedRelativeLocation[3];
	static float userProvidedRelativeRotation[3];
	static float userProvidedRelativeScale[3];
	
	
	if (ImGui::Button("Get All (Location, Rotation, Scale)"))
	{
		SDK::FVector actorLocation = Unreal::Actor::GetLocation(actorReference);
		userProvidedLocation[0] = actorLocation.X; userProvidedLocation[1] = actorLocation.Y; userProvidedLocation[2] = actorLocation.Z;
		locationSource = actorReference;

		SDK::FRotator actorRotation = Unreal::Actor::GetRotation(actorReference);
		userProvidedRotation[0] = actorRotation.Pitch; userProvidedRotation[1] = actorRotation.Yaw; userProvidedRotation[2] = actorRotation.Roll;
		rotationSource = actorReference;

		SDK::FVector actorScale = Unreal::Actor::GetScale3D(actorReference);
		userProvidedScale[0] = actorScale.X; userProvidedScale[1] = actorScale.Y; userProvidedScale[2] = actorScale.Z;
		scaleSource = actorReference;


		SDK::FVector actorRelativeLocation = Unreal::Actor::GetRelativeLocation(actorReference);
		userProvidedRelativeLocation[0] = actorRelativeLocation.X; userProvidedRelativeLocation[1] = actorRelativeLocation.Y; userProvidedRelativeLocation[2] = actorRelativeLocation.Z;
		relativeLocationSource = actorReference;

		SDK::FRotator actorRelativeRotation = Unreal::Actor::GetRelativeRotation(actorReference);
		userProvidedRelativeRotation[0] = actorRelativeRotation.Pitch; userProvidedRelativeRotation[1] = actorRelativeRotation.Yaw; userProvidedRelativeRotation[2] = actorRelativeRotation.Roll;
		relativeRotationSource = actorReference;

		SDK::FVector actorRelativeScale3D = Unreal::Actor::GetRelativeScale3D(actorReference);
		userProvidedRelativeScale[0] = actorRelativeScale3D.X; userProvidedRelativeScale[1] = actorRelativeScale3D.Y; userProvidedRelativeScale[2] = actorRelativeScale3D.Z;
		relativeScaleSource = actorReference;

		GUI::PlayActionSound(true);
	}

	ImGui::Separator();

	ImGui::Text("Location");
	if (ImGui::Button("Get##Location"))
	{
		SDK::FVector actorLocation = Unreal::Actor::GetLocation(actorReference);

		userProvidedLocation[0] = actorLocation.X;
		userProvidedLocation[1] = actorLocation.Y;
		userProvidedLocation[2] = actorLocation.Z;

		locationSource = actorReference;
		GUI::PlayActionSound(true);
	}
	ImGui::SameLine();
	if (actorReference != locationSource)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::Color::Red);
		ImGui::InputFloat3("##Location", userProvidedLocation);
		ImGui::PopStyleColor();
	}
	else
	{
		ImGui::InputFloat3("##Location", userProvidedLocation);
	}
	ImGui::SameLine();
	if (ImGui::Button("Set##Location"))
	{
		bool wasSuccessfull = Unreal::Actor::TeleportTo(actorReference, SDK::FVector(userProvidedLocation[0], userProvidedLocation[1], userProvidedLocation[2]));

		if (wasSuccessfull)
			locationSource = actorReference;

		GUI::PlayActionSound(wasSuccessfull);
	}

	ImGui::Text("Rotation");
	if (ImGui::Button("Get##Rotation"))
	{
		SDK::FRotator actorRotation = Unreal::Actor::GetRotation(actorReference);

		userProvidedRotation[0] = actorRotation.Pitch;
		userProvidedRotation[1] = actorRotation.Yaw;
		userProvidedRotation[2] = actorRotation.Roll;

		rotationSource = actorReference;
		GUI::PlayActionSound(true);
	}
	ImGui::SameLine();
	if (actorReference != rotationSource)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::Color::Red);
		ImGui::InputFloat3("##Rotation", userProvidedRotation);
		ImGui::PopStyleColor();
	}
	else
	{
		ImGui::InputFloat3("##Rotation", userProvidedRotation);
	}
	ImGui::SameLine();
	if (ImGui::Button("Set##Rotation"))
	{
		bool wasSuccessfull = Unreal::Actor::TeleportTo(actorReference, SDK::FRotator(userProvidedRotation[0], userProvidedRotation[1], userProvidedRotation[2]));
		
		if (wasSuccessfull)
			rotationSource = actorReference;

		GUI::PlayActionSound(wasSuccessfull);
	}

	ImGui::Text("Scale");
	if (ImGui::Button("Get##Scale"))
	{
		SDK::FVector actorScale = Unreal::Actor::GetScale3D(actorReference);

		userProvidedScale[0] = actorScale.X;
		userProvidedScale[1] = actorScale.Y;
		userProvidedScale[2] = actorScale.Z;

		scaleSource = actorReference;
		GUI::PlayActionSound(true);
	}
	ImGui::SameLine();
	if (actorReference != scaleSource)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::Color::Red);
		ImGui::InputFloat3("##Scale", userProvidedScale);
		ImGui::PopStyleColor();
	}
	else
	{
		ImGui::InputFloat3("##Scale", userProvidedScale);
	}
	ImGui::SameLine();
	if (ImGui::Button("Set##Scale"))
	{
		bool wasSuccessfull = Unreal::Actor::SetScale3D(actorReference, SDK::FVector(userProvidedScale[0], userProvidedScale[1], userProvidedScale[2]));
		
		if (wasSuccessfull)
			scaleSource = actorReference;

		GUI::PlayActionSound(wasSuccessfull);
	}
	if (ImGui::TreeNode("Relative##LocationRotationScale"))
	{
		ImGui::Text("Location (Relative)");
		if (ImGui::Button("Get##RelativeLocation"))
		{
			SDK::FVector actorRelativeLocation = Unreal::Actor::GetRelativeLocation(actorReference);

			userProvidedRelativeLocation[0] = actorRelativeLocation.X;
			userProvidedRelativeLocation[1] = actorRelativeLocation.Y;
			userProvidedRelativeLocation[2] = actorRelativeLocation.Z;

			relativeLocationSource = actorReference;
			GUI::PlayActionSound(true);
		}
		ImGui::SameLine();
		if (actorReference != relativeLocationSource)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImGui::Color::Red);
			ImGui::InputFloat3("##RelativeLocation", userProvidedRelativeLocation);
			ImGui::PopStyleColor();
		}
		else
		{
			ImGui::InputFloat3("##RelativeLocation", userProvidedRelativeLocation);
		}
		ImGui::SameLine();
		if (ImGui::Button("Set##RelativeLocation"))
		{
			bool wasSuccessfull = Unreal::Actor::RelativeTeleportTo(actorReference, SDK::FVector(userProvidedRelativeLocation[0], userProvidedRelativeLocation[1], userProvidedRelativeLocation[2]));

			if (wasSuccessfull)
				relativeLocationSource = actorReference;

			GUI::PlayActionSound(wasSuccessfull);
		}

		ImGui::Text("Rotation (Relative)");
		if (ImGui::Button("Get##RelativeRotation"))
		{
			SDK::FRotator actorRelativeRotation = Unreal::Actor::GetRelativeRotation(actorReference);

			userProvidedRelativeRotation[0] = actorRelativeRotation.Pitch;
			userProvidedRelativeRotation[1] = actorRelativeRotation.Yaw;
			userProvidedRelativeRotation[2] = actorRelativeRotation.Roll;

			relativeRotationSource = actorReference;
			GUI::PlayActionSound(true);
		}
		ImGui::SameLine();
		if (actorReference != relativeRotationSource)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImGui::Color::Red);
			ImGui::InputFloat3("##RelativeRotation", userProvidedRelativeRotation);
			ImGui::PopStyleColor();
		}
		else
		{
			ImGui::InputFloat3("##RelativeRotation", userProvidedRelativeRotation);
		}
		ImGui::SameLine();
		if (ImGui::Button("Set##RelativeRotation"))
		{
			bool wasSuccessfull = Unreal::Actor::RelativeTeleportTo(actorReference, SDK::FRotator(userProvidedRelativeRotation[0], userProvidedRelativeRotation[1], userProvidedRelativeRotation[2]));

			if (wasSuccessfull)
				relativeRotationSource = actorReference;

			GUI::PlayActionSound(wasSuccessfull);
		}

		ImGui::Text("Scale (Relative)");
		if (ImGui::Button("Get##RelativeScale"))
		{
			SDK::FVector actorRelativeScale = Unreal::Actor::GetRelativeScale3D(actorReference);

			userProvidedRelativeScale[0] = actorRelativeScale.X;
			userProvidedRelativeScale[1] = actorRelativeScale.Y;
			userProvidedRelativeScale[2] = actorRelativeScale.Z;

			relativeScaleSource = actorReference;
			GUI::PlayActionSound(true);
		}
		ImGui::SameLine();
		if (actorReference != relativeScaleSource)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImGui::Color::Red);
			ImGui::InputFloat3("##RelativeScale", userProvidedRelativeScale);
			ImGui::PopStyleColor();
		}
		else
		{
			ImGui::InputFloat3("##RelativeScale", userProvidedRelativeScale);
		}
		ImGui::SameLine();
		if (ImGui::Button("Set##RelativeScale"))
		{
			bool wasSuccessfull = Unreal::Actor::SetRelativeScale3D(actorReference, SDK::FVector(userProvidedRelativeScale[0], userProvidedRelativeScale[1], userProvidedRelativeScale[2]));

			if (wasSuccessfull)
				relativeScaleSource = actorReference;

			GUI::PlayActionSound(wasSuccessfull);
		}

		ImGui::TreePop();
	}
}




void Templates::Descriptions::HDR::Draw()
{
#ifndef UE5
	ImGui::TitleText("[!] DirectX 12 [!]");
	ImGui::Text("Unreal Engine 4.14 - 4.27 only support HDR while running under DirectX 11.");
	ImGui::NewLine();
#endif

	ImGui::SetFontSmall();
	ImGui::Text("HDR must be allowed through configuration file in order to be enabled.");

	ImGui::SetFontRegular();
	ImGui::Text("DefaultEngine.ini | UserEngine.ini | Engine.ini");
	ImGui::SetFontSmall();
	static const char* HDRAllowConfigDescription = "[/Script/Engine.RendererSettings]\n"
		"r.AllowHDR = 1";
	static const size_t HDRAllowConfigDescriptionLength = strlen(HDRAllowConfigDescription);
	ImGui::InputTextMultiline("##HDRAllowConfigDescription", const_cast<char*>(HDRAllowConfigDescription), HDRAllowConfigDescriptionLength, { 500, 120 }, ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	if (ImGui::Button("Copy##HDRAllowConfigDescription"))
	{
		GUI::PlayActionSound(Utilities::Clipboard::SetText(HDRAllowConfigDescription));
	}

	ImGui::NewLine();

	ImGui::Text("Behavior can be adjusted through configuration file or Unreal Engine Console (Engine -> Game Viewport Client -> Console).");

	ImGui::SetFontRegular();
	ImGui::Text("DefaultEngine.ini | UserEngine.ini | Engine.ini");
	ImGui::SetFontSmall();
	static const char* HDRSettingsConfigDescription =
		"[/Script/Engine.RendererSettings]\n"
		"r.HDR.EnableHDROutput = 1\n"
		"; 0 - LDR.\n"
		"; 1 - HDR.\n"
		"\n"
		"r.HDR.Display.ColorGamut = 2\n"
		"; Color space of the output display.\n"
		"; 0 - Rec709.\n"
		"; 1 - DCI - P3.\n"
		"; 2 - Rec2020.\n"
		"; 3 - ACES.\n"
		"; 4 - ACEScg.\n"
		"\n"
		"r.HDR.Display.OutputDevice = 5\n"
		"; Device format of the output display\n"
		"; 0 - sRGB (LDR).\n"
		"; 1 - Rec709 (LDR).\n"
		"; 2 - Explicit gamma mapping (LDR).\n"
		"; 3 - ACES 1000 nit ST-2084 (Dolby PQ) (HDR).\n"
		"; 4 - ACES 2000 nit ST-2084 (Dolby PQ) (HDR).\n"
		"; 5 - ACES 1000 nit ScRGB (HDR).\n"
		"; 6 - ACES 2000 nit ScRGB (HDR).\n"
		"; 7 - Linear EXR (HDR).\n"
		"; 8 - Linear final color, no tone curve (HDR).\n"
		"; 9 - Linear final color with tone curve (HDR).\n"
		"\n"
#ifdef UE5																		  										  
		"r.HDR.Display.MaxLuminance = 1000\n"
		"; Output peak nit level.\n"
		"\n"
		"r.HDR.Display.MidLuminance = 15\n"
		"; Output nit level for 18% gray."
		"\n"
#endif																			  										  
		"r.HDR.UI.CompositeMode = 1\n"
		"; Preserve LDR visuals and blending for UI elements.\n"
		"\n"
		"r.HDR.UI.Level = 0.65\n"
		"; Luminance level for UI elements.";
	static const size_t HDRSettingsConfigDescriptionLength = strlen(HDRSettingsConfigDescription);
	ImGui::InputTextMultiline("##HDRSettingsConfigDescription", const_cast<char*>(HDRSettingsConfigDescription), HDRSettingsConfigDescriptionLength, { 800, 600 }, ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	if (ImGui::Button("Copy##HDRSettingsConfigDescription"))
	{
		GUI::PlayActionSound(Utilities::Clipboard::SetText(HDRSettingsConfigDescription));
	}

	ImGui::SetFontRegular();
	ImGui::Text("Unreal Engine Console");
	ImGui::SetFontSmall();
	static const char* HDRSettingsConsoleDescription =
		"r.HDR.EnableHDROutput 1 | "
		"r.HDR.Display.ColorGamut 2 | "
		"r.HDR.Display.OutputDevice 5 | "
#ifdef UE5																		   
		"r.HDR.Display.MaxLuminance 1000 | "
		"r.HDR.Display.MidLuminance 15 | "
#endif																			   
		"r.HDR.UI.CompositeMode 1 | "
		"r.HDR.UI.Level 0.65";
	static const size_t HDRSettingsConsoleDescriptionLength = strlen(HDRSettingsConsoleDescription);
	ImGui::InputTextMultiline("##HDRSettingsConsoleDescription", const_cast<char*>(HDRSettingsConsoleDescription), HDRSettingsConsoleDescriptionLength, { 800, 40 }, ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	if (ImGui::Button("Copy##HDRSettingsConsoleDescription"))
	{
		GUI::PlayActionSound(Utilities::Clipboard::SetText(HDRSettingsConsoleDescription));
	}

	ImGui::NewLine();

	ImGui::Text("Autoexposure and fake HDR can cause scenes to appear overly dark.");

	ImGui::SetFontRegular();
	ImGui::Text("DefaultEngine.ini | UserEngine.ini | Engine.ini");
	ImGui::SetFontSmall();
	static const char* HDRDisturbanceConfigDescription = "[/Script/Engine.RendererSettings]\n"
		"r.DefaultFeature.AutoExposure = 0\n"
		"r.EyeAdaptationQuality = 0";
	static const size_t HDRDisturbanceConfigDescriptionLength = strlen(HDRDisturbanceConfigDescription);
	ImGui::InputTextMultiline("##HDRDisturbanceConfigDescription", const_cast<char*>(HDRDisturbanceConfigDescription), HDRDisturbanceConfigDescriptionLength, { 500, 120 }, ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	if (ImGui::Button("Copy##HDRDisturbanceConfigDescription"))
	{
		GUI::PlayActionSound(Utilities::Clipboard::SetText(HDRDisturbanceConfigDescription));
	}

	ImGui::SetFontRegular();
	ImGui::Text("Unreal Engine Console");
	ImGui::SetFontSmall();
	static const char* HDRDisturbanceConsoleDescription = "r.DefaultFeature.AutoExposure 0 | "
		"r.EyeAdaptationQuality 0";
	static const size_t HDRDisturbanceConsoleDescriptionLength = strlen(HDRDisturbanceConsoleDescription);
	ImGui::InputTextMultiline("##HDRDisturbanceConsoleDescription", const_cast<char*>(HDRDisturbanceConsoleDescription), HDRDisturbanceConsoleDescriptionLength, { 800, 40 }, ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	if (ImGui::Button("Copy##HDRDisturbanceConsoleDescription"))
	{
		GUI::PlayActionSound(Utilities::Clipboard::SetText(HDRDisturbanceConsoleDescription));
	}

	ImGui::NewLine();

	ImGui::Text("Certain titles may try deleting \"Engine.ini\" configuration file from the system!\nIt's recommended to set it as for read-only (RMB -> Properties).");

	ImGui::SetFontRegular();
}


#ifdef SOFT_PATH
void Templates::Descriptions::SoftPath::Draw(const char* typeName, const char* examplePath)
{
	ImGui::SetFontSmall();
	ImGui::Text("Dynamic %s loading by soft path, for example \"%s\".", typeName ? typeName : "#TYPE#", examplePath ? examplePath : "#EXAMPLEPATH#");
	ImGui::SameLine();
	ImGui::QuestionMarkHint("Format: Automatically converts FModel/Windows paths to UE-native.\nShortcut: Use '--' (.{name}) or '..' (.{name}_C) suffixes to complete the path.\nMulti-input: Use '|' as a separator between paths.");
	ImGui::SetFontRegular();
}
#endif




void Templates::Menus::Debug::Sub_Engine()
{
	ImGui::SetFontTitle();
	ImGui::TextBoolPresenceColored("Engine:", Features::Debug::engine.reference);
	ImGui::SetFontRegular();
	if (Features::Debug::engine.reference)
	{
		if (ImGui::CollapsingHeader("Details##Engine"))
		{
			ImGui::TextCopyable("Engine Class: %s", Features::Debug::engine.className.c_str());
			ImGui::TextCopyable("Engine Object: %s", Features::Debug::engine.objectName.c_str());

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Game Viewport Client:", Features::Debug::engine.gameViewportClient.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::engine.gameViewportClient.reference)
			{
				if (ImGui::TreeNode("Details##GameViewportClient"))
				{
					ImGui::TextCopyable("Viewport Client Class: %s", Features::Debug::engine.gameViewportClient.className.c_str());
					ImGui::TextCopyable("Viewport Client Object: %s", Features::Debug::engine.gameViewportClient.objectName.c_str());

					ImGui::NewLine();

					ImGui::SetFontTitle();
					ImGui::TextBoolPresenceColored("Console:", Features::Debug::engine.gameViewportClient.console.reference);
					ImGui::SetFontRegular();
					if (Features::Debug::engine.gameViewportClient.console.reference)
					{
						ImGui::SameLine();
						ImGui::QuestionMarkHint("Press ~ (Tilde) or F10 to open. Second press will switch console to detailed mode.");

						if (ImGui::TreeNode("Details##Console"))
						{
							ImGui::TextCopyable("Console Class: %s", Features::Debug::engine.gameViewportClient.console.className.c_str());
							ImGui::TextCopyable("Console Object: %s", Features::Debug::engine.gameViewportClient.console.objectName.c_str());

							ImGui::NewLine();
							ImGui::SetFontBig();
							ImGui::Text("Console Commands");
							ImGui::SetFontRegular();
							ImGui::SameLine();
							ImGui::QuestionMarkHint("Scans all instantiated UObjects for Exec (console) commands.");
							if (ImGui::Button("Update##ConsoleCommands"))
							{
								Features::ConsoleCommands::Update();
								GUI::PlayActionSound(true);
							}
							ImGui::SameLine();
							ImGui::Spacing();
							ImGui::SameLine();
							ImGui::InputText("Search Filter##ConsoleCommands", Features::ConsoleCommands::filterBuffer, Features::ConsoleCommands::filterBufferSize);
							ImGui::SameLine();
							ImGui::Spacing();
							ImGui::SameLine();
							ImGui::Checkbox("Case Sensitive##ConsoleCommands", &Features::ConsoleCommands::filterCaseSensitive);

							std::vector<Unreal::Function::DataStructure> filteredCommands = Unreal::Function::FilterByName(Features::ConsoleCommands::commands, Features::ConsoleCommands::filterBuffer, Features::ConsoleCommands::filterCaseSensitive);
							for (Unreal::Function::DataStructure function : filteredCommands)
							{
								std::string memoryAddress = function.MemoryAddressAsString();
								ImGui::PushID(memoryAddress.c_str());

								if (ImGui::TreeNode(function.name.c_str()))
								{
									ImGui::TextCopyable("Flags: %s", function.FlagsAsString().c_str());
									ImGui::TextCopyable("Address: %s", memoryAddress.c_str());

									ImGui::TreePop();
								}

								ImGui::PopID();
							}

							ImGui::TreePop();
						}
					}
					else
					{
						if (ImGui::Button("Construct Console"))
						{
							bool wasConstructed = Unreal::Console::Construct() && Unreal::InputSettings::AssignConsoleBindings();
							if (wasConstructed) // Only gather debug information if we're aware of changes.
								Features::Debug::Update_ThreadSafe();

							GUI::PlayActionSound(wasConstructed);
						}
					}

					ImGui::TreePop();
				}
			}

			ImGui::NewLine();

			ImGui::TitleText("High Dynamic Range");
			if (ImGui::TreeNode("Details##HDR"))
			{
				Templates::Descriptions::HDR::Draw();
				ImGui::TreePop();
			}


			ImGui::NewLine();

			bool fixedFrameRateEnabled = Features::Debug::engine.fixedFrameRateEnabled;
			if (ImGui::Checkbox("Fixed FrameRate Enabled", &fixedFrameRateEnabled))
			{
				if (Features::Debug::engine.reference)
				{
					Features::Debug::engine.fixedFrameRateEnabled = fixedFrameRateEnabled;
					Features::Debug::engine.reference->bUseFixedFrameRate = fixedFrameRateEnabled;
				}
			}
			float fixedFrameRate = Features::Debug::engine.fixedFrameRate;
			if (ImGui::InputFloat("Fixed FrameRate", &fixedFrameRate, 1.0f, 10.0f))
			{
				if (Features::Debug::engine.reference)
				{
					Features::Debug::engine.fixedFrameRate = fixedFrameRate;
					Features::Debug::engine.reference->FixedFrameRate = fixedFrameRate;
				}
			}

			ImGui::NewLine();

			bool smoothFrameRateEnabled = Features::Debug::engine.smoothFrameRateEnabled;
			if (ImGui::Checkbox("Smooth FrameRate Enabled", &smoothFrameRateEnabled))
			{
				if (Features::Debug::engine.reference)
				{
					Features::Debug::engine.smoothFrameRateEnabled = smoothFrameRateEnabled;
					Features::Debug::engine.reference->bSmoothFrameRate = smoothFrameRateEnabled;
				}
			}
			float smoothFrameRateRange[2] = { Features::Debug::engine.smoothFrameRateRange.LowerBound.Value, Features::Debug::engine.smoothFrameRateRange.UpperBound.Value };
			if (ImGui::InputFloat2("Smooth FrameRate Range", smoothFrameRateRange))
			{
				if (Features::Debug::engine.reference)
				{
					SDK::FFloatRange floatRange = Features::Debug::engine.smoothFrameRateRange;
					floatRange.LowerBound.Value = smoothFrameRateRange[0];
					floatRange.UpperBound.Value = smoothFrameRateRange[1];

					Features::Debug::engine.smoothFrameRateRange = floatRange;
					Features::Debug::engine.reference->SmoothedFrameRateRange = floatRange;
				}
			}

			ImGui::NewLine();

			bool subtitlesEnabled = Features::Debug::engine.subtitlesEnabled;
			if (ImGui::Checkbox("Subtitles Enabled", &subtitlesEnabled))
			{
				if (Features::Debug::engine.reference)
				{
					Features::Debug::engine.subtitlesEnabled = subtitlesEnabled;
					Features::Debug::engine.reference->bSubtitlesEnabled = subtitlesEnabled;
				}
			}
			bool subtitlesForcedOff = Features::Debug::engine.subtitlesForcedOff;
			if (ImGui::Checkbox("Subtitles Forced Off", &subtitlesForcedOff))
			{
				if (Features::Debug::engine.reference)
				{
					Features::Debug::engine.subtitlesForcedOff = subtitlesForcedOff;
					Features::Debug::engine.reference->bSubtitlesForcedOff = subtitlesForcedOff;
				}
			}

			ImGui::NewLine();

			bool pauseOnLossOfFocus = Features::Debug::engine.pauseOnLossOfFocus;
			if (ImGui::Checkbox("Pause On Loss Of Focus", &pauseOnLossOfFocus))
			{
				if (Features::Debug::engine.reference)
				{
					Features::Debug::engine.pauseOnLossOfFocus = pauseOnLossOfFocus;
					Features::Debug::engine.reference->bPauseOnLossOfFocus = pauseOnLossOfFocus;
				}
			}
		}
	}
}

void Templates::Menus::Debug::Sub_GameInstance()
{
	ImGui::SetFontTitle();
	ImGui::TextBoolPresenceColored("Game Instance:", Features::Debug::gameInstance.reference);
	ImGui::SetFontRegular();
	if (Features::Debug::gameInstance.reference)
	{
		if (ImGui::CollapsingHeader("Details##GameInstance"))
		{
			ImGui::TextCopyable("Game Instance Class: %s", Features::Debug::gameInstance.className.c_str());
			ImGui::TextCopyable("Game Instance Object: %s", Features::Debug::gameInstance.objectName.c_str());

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Online Session:", Features::Debug::gameInstance.onlineSession.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::gameInstance.onlineSession.reference)
			{
				if (ImGui::TreeNode("Details##OnlineSession"))
				{
					ImGui::TextCopyable("Online Session Class: %s", Features::Debug::gameInstance.onlineSession.className.c_str());
					ImGui::TextCopyable("Online Session Object: %s", Features::Debug::gameInstance.onlineSession.objectName.c_str());

					ImGui::TreePop();
				}
			}
		}
	}
}

void Templates::Menus::Debug::Sub_GameMode()
{
	ImGui::SetFontTitle();
	ImGui::TextBoolPresenceColored("Game Mode:", Features::Debug::gameMode.reference);
	ImGui::SetFontRegular();
	if (Features::Debug::gameMode.reference)
	{
		if (ImGui::CollapsingHeader("Details##GameMode"))
		{
			ImGui::TextCopyable("Game Mode Class: %s", Features::Debug::gameMode.className.c_str());
			ImGui::TextCopyable("Game Mode Object: %s", Features::Debug::gameMode.objectName.c_str());

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Game Session:", Features::Debug::gameMode.gameSession.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::gameMode.gameSession.reference)
			{
				if (ImGui::TreeNode("Details##GameSession"))
				{
					ImGui::TextCopyable("Game Session Class: %s", Features::Debug::gameMode.gameSession.className.c_str());
					ImGui::TextCopyable("Game Session Object: %s", Features::Debug::gameMode.gameSession.objectName.c_str());

					ImGui::NewLine();

					int32_t maxPlayers = Features::Debug::gameMode.gameSession.maxPlayers;
					if (ImGui::InputInt("Max Players", &maxPlayers, 1, 10))
					{
						if (Features::Debug::gameMode.gameSession.reference)
						{
							Features::Debug::gameMode.gameSession.maxPlayers = maxPlayers;
							Features::Debug::gameMode.gameSession.reference->MaxPlayers = maxPlayers;
						}
					}
					int32_t maxSpectators = Features::Debug::gameMode.gameSession.maxSpectators;
					if (ImGui::InputInt("Max Spectators", &maxSpectators, 1, 10))
					{
						if (Features::Debug::gameMode.gameSession.reference)
						{
							Features::Debug::gameMode.gameSession.maxSpectators = maxSpectators;
							Features::Debug::gameMode.gameSession.reference->MaxSpectators = maxSpectators;
						}
					}
					int32_t maxPartySize = Features::Debug::gameMode.gameSession.maxPartySize;
					if (ImGui::InputInt("Max Party Size", &maxPartySize, 1, 10))
					{
						if (Features::Debug::gameMode.gameSession.reference)
						{
							Features::Debug::gameMode.gameSession.maxPartySize = maxPartySize;
							Features::Debug::gameMode.gameSession.reference->MaxPartySize = maxPartySize;
						}
					}
					int32_t maxSplitScreensPerConnection = Features::Debug::gameMode.gameSession.maxSplitScreensPerConnection;
					if (ImGui::InputInt("Max Split Screens Per Connection", &maxSplitScreensPerConnection, 1, 10))
					{
						if (Features::Debug::gameMode.gameSession.reference)
						{
							Features::Debug::gameMode.gameSession.maxSplitScreensPerConnection = maxSplitScreensPerConnection;
							Features::Debug::gameMode.gameSession.reference->MaxSplitscreensPerConnection = maxSplitScreensPerConnection;
						}
					}

					ImGui::NewLine();

					ImGui::ReadOnlyInputText("Session Name:", Features::Debug::gameMode.gameSession.sessionName.c_str());

					ImGui::TreePop();
				}
			}

			ImGui::NewLine();

			ImGui::TextIntColored("Players Count:", Features::Debug::gameMode.playersCount);
			ImGui::TextIntColored("Spectators Count:", Features::Debug::gameMode.spectatorsCount);

			ImGui::NewLine();

			ImGui::TextBoolColored("Start Players As Spectator:", Features::Debug::gameMode.startPlayersAsSpectators);
			ImGui::ReadOnlyInputText("Default Player Name:", Features::Debug::gameMode.defaultPlayerName.c_str());

			ImGui::NewLine();

			bool useSeamlessTravel = Features::Debug::gameMode.useSeamlessTravel;
			if (ImGui::Checkbox("Use Seamless Travel", &useSeamlessTravel))
			{
				if (Features::Debug::gameMode.reference)
				{
					Features::Debug::gameMode.useSeamlessTravel = useSeamlessTravel;
					Features::Debug::gameMode.reference->bUseSeamlessTravel = useSeamlessTravel;
				}
			}
			bool isPausable = Features::Debug::gameMode.isPausable;
			if (ImGui::Checkbox("Is Pausable", &isPausable))
			{
				if (Features::Debug::gameMode.reference)
				{
					Features::Debug::gameMode.isPausable = isPausable;
					Features::Debug::gameMode.reference->bPauseable = isPausable;
				}
			}

			ImGui::NewLine();

			ImGui::ReadOnlyInputText("Options:", Features::Debug::gameMode.options.c_str());
		}
	}
}

void Templates::Menus::Debug::Sub_PlayerController()
{
	ImGui::SetFontTitle();
	ImGui::TextBoolPresenceColored("Player Controller:", Features::Debug::playerController.reference);
	ImGui::SetFontRegular();
	if (Features::Debug::playerController.reference)
	{
		if (ImGui::CollapsingHeader("Details##PlayerController"))
		{
			ImGui::TextCopyable("Player Controller Class: %s", Features::Debug::playerController.className.c_str());
			ImGui::TextCopyable("Player Controller Object: %s", Features::Debug::playerController.objectName.c_str());

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Pawn:", Features::Debug::playerController.pawn.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::playerController.pawn.reference)
			{
				if (ImGui::TreeNode("Details##Pawn"))
				{
					ImGui::TextCopyable("Pawn Class: %s", Features::Debug::playerController.pawn.className.c_str());
					ImGui::TextCopyable("Pawn Object: %s", Features::Debug::playerController.pawn.objectName.c_str());

					ImGui::NewLine();

					ImGui::TextVectorColored("Cached Location:", Features::Debug::playerController.pawn.transform.location);
					ImGui::TextRotatorColored("Cached Rotation:", Features::Debug::playerController.pawn.transform.rotation);
					ImGui::TextVectorColored("Cached Scale:   ", Features::Debug::playerController.pawn.transform.scale);

					ImGui::NewLine();

					ImGui::TextBoolColored("Is Controlled:", Features::Debug::playerController.pawn.isControlled);
					ImGui::TextBoolColored("Is Pawn Controlled:", Features::Debug::playerController.pawn.isPawnControlled);
					ImGui::TextBoolColored("Is Player Controlled:", Features::Debug::playerController.pawn.isPlayerControlled);
					ImGui::TextBoolColored("Is Locally Controlled:", Features::Debug::playerController.pawn.isLocallyControlled);
					ImGui::TextBoolColored("Is Bot Controlled:", Features::Debug::playerController.pawn.isBotControlled);

					ImGui::TreePop();
				}
			}

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Camera Manager:", Features::Debug::playerController.cameraManager.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::playerController.cameraManager.reference)
			{
				if (ImGui::TreeNode("Details##CameraManager"))
				{
					ImGui::TextCopyable("Camera Manager Class: %s", Features::Debug::playerController.cameraManager.className.c_str());
					ImGui::TextCopyable("Camera Manager Object: %s", Features::Debug::playerController.cameraManager.objectName.c_str());
					ImGui::TextVectorColored("Cached Location:", Features::Debug::playerController.cameraManager.transform.location);
					ImGui::TextRotatorColored("Cached Rotation:", Features::Debug::playerController.cameraManager.transform.rotation);
					ImGui::TextVectorColored("Cached Scale:   ", Features::Debug::playerController.cameraManager.transform.scale);
					Templates::LocationRotationScale::Draw(Features::Debug::playerController.cameraManager.reference);

					ImGui::TreePop();
				}
			}

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Cheat Manager:", Features::Debug::playerController.cheatManager.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::playerController.cheatManager.reference)
			{
				if (ImGui::TreeNode("Details##CheatManager"))
				{
					ImGui::TextCopyable("Cheat Manager Class: %s", Features::Debug::playerController.cheatManager.className.c_str());
					ImGui::TextCopyable("Cheat Manager Object: %s", Features::Debug::playerController.cheatManager.objectName.c_str());

					ImGui::TreePop();
				}
			}
			else
			{
				if (ImGui::Button("Construct Cheat Manager"))
				{
					bool wasConstructed = Unreal::CheatManager::Construct();
					if (wasConstructed) // Only gather debug information if we're aware of changes.
						Features::Debug::Update_ThreadSafe();

					GUI::PlayActionSound(wasConstructed);
				}
			}
		}
	}
}

void Templates::Menus::Debug::Sub_World()
{
	ImGui::SetFontTitle();
	ImGui::TextBoolPresenceColored("World:", Features::Debug::world.reference);
	ImGui::SetFontRegular();
	if (Features::Debug::world.reference)
	{
		if (ImGui::CollapsingHeader("Details##World"))
		{
			ImGui::TextCopyable("World Class: %s", Features::Debug::world.className.c_str());
			ImGui::TextCopyable("World Object: %s", Features::Debug::world.objectName.c_str());

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Game State:", Features::Debug::world.gameState.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::world.gameState.reference)
			{
				if (ImGui::TreeNode("Details##GameState"))
				{
					ImGui::TextCopyable("Game State Class: %s", Features::Debug::world.gameState.className.c_str());
					ImGui::TextCopyable("Game State Object: %s", Features::Debug::world.gameState.objectName.c_str());

					ImGui::TreePop();
				}
			}

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Net Driver:", Features::Debug::world.netDriver.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::world.netDriver.reference)
			{
				if (ImGui::TreeNode("Details##NetDriver"))
				{
					ImGui::TextCopyable("Net Driver Class: %s", Features::Debug::world.netDriver.className.c_str());
					ImGui::TextCopyable("Net Driver Object: %s", Features::Debug::world.netDriver.objectName.c_str());

					ImGui::TreePop();
				}
			}

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Demo Net Driver:", Features::Debug::world.demoNetDriver.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::world.demoNetDriver.reference)
			{
				if (ImGui::TreeNode("Details##DemoNetDriver"))
				{
					ImGui::TextCopyable("Demo Net Driver Class: %s", Features::Debug::world.demoNetDriver.className.c_str());
					ImGui::TextCopyable("Demo Net Driver Object: %s", Features::Debug::world.demoNetDriver.objectName.c_str());

					ImGui::TreePop();
				}
			}

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Persistent Level:", Features::Debug::world.persistentLevel.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::world.persistentLevel.reference)
			{
				if (ImGui::TreeNode("Details##PersistentLevel"))
				{
					ImGui::TextCopyable("Persistent Level Class: %s", Features::Debug::world.persistentLevel.className.c_str());
					ImGui::TextCopyable("Persistent Level Object: %s", Features::Debug::world.persistentLevel.objectName.c_str());
					ImGui::TextBoolColored("Is Visible:", Features::Debug::world.persistentLevel.isVisible);

					ImGui::NewLine();

					bool worldSettingsPresent = Features::Debug::world.persistentLevel.worldSettings.reference;
					ImGui::TextBoolPresenceColored("World Settings:", worldSettingsPresent);
					if (worldSettingsPresent)
					{
						if (ImGui::TreeNode("Details##WorldSettings"))
						{
							ImGui::TextCopyable("World Settings Class: %s", Features::Debug::world.persistentLevel.worldSettings.className.c_str());
							ImGui::TextCopyable("World Settings Object: %s", Features::Debug::world.persistentLevel.worldSettings.objectName.c_str());

							ImGui::NewLine();

							ImGui::TextBoolColored("High Priority Loading:", Features::Debug::world.persistentLevel.worldSettings.highPriorityLoading);
							ImGui::TextBoolColored("Local High Priority Loading:", Features::Debug::world.persistentLevel.worldSettings.localHighPriorityLoading);

							ImGui::NewLine();

							ImGui::Text("Units: 1m = %.2f", Features::Debug::world.persistentLevel.worldSettings.unitsToMeters);

							ImGui::TreePop();
						}
					}

					ImGui::NewLine();

					ImGui::TextFloatColored("Game Time (In Seconds):", Features::Debug::world.gameTimeInSeconds);

					ImGui::NewLine();

					ImGui::TextBoolColored("Is Server:", Features::Debug::world.isServer);
					ImGui::TextBoolColored("Is Dedicated Server:", Features::Debug::world.isDedicatedServer);
					ImGui::TextBoolColored("Is Split Screen:", Features::Debug::world.isSplitScreen);
					ImGui::TextBoolColored("Is Standalone:", Features::Debug::world.isStandalone);

					ImGui::TreePop();
				}
			}
		}
	}
}

void Templates::Menus::Debug::Sub_Actors()
{
	ImGui::TitleText("Actors");
	if (ImGui::CollapsingHeader("Details##Actors"))
	{
		ImGui::TitleText("Trace");
		ImGui::SmallText("Projects a trace from the camera's position and outputs the name of the Actor hit by it.");
		ImGui::SmallText("X - Location at where trace has hit an Actor.");
		ImGui::SmallText("@ - Location at where trace has ended without a hit.");
		ImGui::SmallText("O - Location at where trace has started.");
		if (ImGui::TreeNode("Details##Trace"))
		{
			if (ImGui::Button("Send Trace"))
			{
				GUI::PlayActionSound(Features::ActorTrace::Trace());
			}
			if (ImGui::KeyBindingInput("Key Binding:##Trace", &Inputs::Keybindings::debug_ActorTrace))
			{
				Features::Config::Save();
			}

			ImGui::NewLine();

			if (ImGui::Checkbox("Show On Screen##Trace", &Features::ActorTrace::showOnScreen))
			{
				Features::Config::Save();
			}

			ImGui::NewLine();

			ImGui::BeginDisabled(Features::ActorTrace::showOnScreen == false);
			if (ImGui::ColorConfig4("Trace Color##Trace", Features::ActorTrace::traceColor))
			{
				Features::Config::Save();
			}

			ImGui::NewLine();

			ImGui::Text("Trace Thickness");
			ImGui::SliderFloatEditable("##Trace##Thickness", &Features::ActorTrace::traceThickness, 1.0f, 10.0f);
			if (ImGui::IsItemDeactivatedAfterEdit())
			{
				Features::Config::Save();
			}

			ImGui::NewLine();

			ImGui::Text("Trace Distance");
			ImGui::SameLine();
			static const std::string distanceHint = std::format("Determines maximum length of trace in metres.\n\n1m = {:.0f}units", Math::Metre_ToUnit(1.0f));
			ImGui::QuestionMarkHint(distanceHint.c_str());
			ImGui::SliderFloatEditable("##Trace##Distance", &Features::ActorTrace::traceDistance, 1.0f, 1000.0f);
			if (ImGui::IsItemDeactivatedAfterEdit())
			{
				Features::Config::Save();
			}
			ImGui::EndDisabled();

			ImGui::NewLine();

#ifdef UE5
			const char* objectName = Features::ActorTrace::object.reference ? Features::ActorTrace::object.objectName.c_str() : "None";
			ImGui::TextCopyable("Traced Object: %s", objectName);
#else
			const char* actorName = Features::ActorTrace::traceHit ? Features::ActorTrace::actor.objectName.c_str() : "None";
			ImGui::TextCopyable("Traced Actor: %s", actorName);
#endif

			ImGui::TreePop();
		}

		ImGui::NewLine();

		ImGui::TitleText("Summon");
#ifdef SOFT_PATH
		Templates::Descriptions::SoftPath::Draw("Actor, Static or Skeletal Mesh", "/Game/Blueprints/BP_CoinPickable.BP_CoinPickable_C | /Game/Models/SM_Cookie.SM_Cookie");
#else
		ImGui::SmallText("Dynamic Actor spawning from ready to go presets.");
#endif

		if (ImGui::TreeNode("Details##Actors##Summon"))
		{
			ImGui::TitleText("From Presets");

			ImGui::BigText("Light");
			if (ImGui::IconButton(Window::texturesCollection.T_Actor_PointLight, "Point Light"))
			{
				bool wasSuccessfull = Unreal::Actor::Summon(SDK::APointLight::StaticClass());
				GUI::PlayActionSound(wasSuccessfull);
			}
			ImGui::SameLine();
			if (ImGui::IconButton(Window::texturesCollection.T_Actor_SpotLight, "Spot Light"))
			{
				bool wasSuccessfull = Unreal::Actor::Summon(SDK::ASpotLight::StaticClass());
				GUI::PlayActionSound(wasSuccessfull);
			}
			ImGui::SameLine();
			if (ImGui::IconButton(Window::texturesCollection.T_Actor_RectLight, "Rect Light"))
			{
				bool wasSuccessfull = Unreal::Actor::Summon(SDK::ARectLight::StaticClass());
				GUI::PlayActionSound(wasSuccessfull);
			}
			ImGui::SameLine();
			if (ImGui::IconButton(Window::texturesCollection.T_Actor_DirectionalLight, "Directional Light"))
			{
				bool wasSuccessfull = Unreal::Actor::Summon(SDK::ADirectionalLight::StaticClass());
				GUI::PlayActionSound(wasSuccessfull);
			}
			ImGui::SameLine();
			if (ImGui::IconButton(Window::texturesCollection.T_Actor_SkyLight, "Sky Light"))
			{
				bool wasSuccessfull = Unreal::Actor::Summon(SDK::ASkyLight::StaticClass());
				GUI::PlayActionSound(wasSuccessfull);
			}

			ImGui::NewLine();

			ImGui::BigText("Fog");
			if (ImGui::IconButton(Window::texturesCollection.T_Actor_AtmosphericFog, "Atmospheric Fog"))
			{
				bool wasSuccessfull = Unreal::Actor::Summon(SDK::AAtmosphericFog::StaticClass());
				GUI::PlayActionSound(wasSuccessfull);
			}
			ImGui::SameLine();
			if (ImGui::IconButton(Window::texturesCollection.T_Actor_ExponentialHeightFog, "Exponential Height Fog"))
			{
				bool wasSuccessfull = Unreal::Actor::Summon(SDK::AExponentialHeightFog::StaticClass());
				GUI::PlayActionSound(wasSuccessfull);
			}

			ImGui::NewLine();

			ImGui::BigText("Technical");
			if (ImGui::IconButton(Window::texturesCollection.T_Actor_Camera, "Camera"))
			{
				bool wasSuccessfull = Unreal::Actor::Summon(SDK::ACameraActor::StaticClass());
				GUI::PlayActionSound(wasSuccessfull);
			}
			ImGui::SameLine();
			if (ImGui::IconButton(Window::texturesCollection.T_Actor_DefaultPawn, "Default Pawn"))
			{
				bool wasSuccessfull = Unreal::Actor::Summon(SDK::ADefaultPawn::StaticClass());
				GUI::PlayActionSound(wasSuccessfull);
			}

			ImGui::NewLine();

			ImGui::BigText("Other");
			if (ImGui::IconButton(Window::texturesCollection.T_Actor_Decal, "Decal"))
			{
				bool wasSuccessfull = Unreal::Actor::Summon(SDK::ADecalActor::StaticClass());
				GUI::PlayActionSound(wasSuccessfull);
			}
			ImGui::SameLine();
			if (ImGui::IconButton(Window::texturesCollection.T_Actor_TextRender, "Text Render"))
			{
				bool wasSuccessfull = Unreal::Actor::Summon(SDK::ATextRenderActor::StaticClass());
				GUI::PlayActionSound(wasSuccessfull);
			}
			ImGui::SameLine();
			if (ImGui::IconButton(Window::texturesCollection.T_Actor_TargetPoint, "Target Point"))
			{
				bool wasSuccessfull = Unreal::Actor::Summon(SDK::ATargetPoint::StaticClass());
				GUI::PlayActionSound(wasSuccessfull);
			}

#ifdef SOFT_PATH
			ImGui::CategorySeparator();

			ImGui::TitleText("From Path");

			ImGui::Text("Soft Path");
			ImGui::InputText("##Actors##Summon##Path", Features::ActorSummon::pathBuffer, Features::ActorSummon::pathBufferSize);

			ImGui::NewLine();

			ImGui::BeginDisabled(Features::ActorSummon::usePlayerLocation);
			ImGui::Text("Location:");
			ImGui::SameLine();
			ImGui::InputFloat3("##Actors##Summon##Location", Features::ActorSummon::location);
			ImGui::EndDisabled();
			ImGui::SameLine();
			ImGui::Checkbox("Use Player Location##Actors##Summon", &Features::ActorSummon::usePlayerLocation);

			ImGui::BeginDisabled(Features::ActorSummon::usePlayerRotation);
			ImGui::Text("Rotation:");
			ImGui::SameLine();
			ImGui::InputFloat3("##Actors##Summon##Rotation", Features::ActorSummon::rotation);
			ImGui::EndDisabled();
			ImGui::SameLine();
			ImGui::Checkbox("Use Player Rotation##Actors##Summon", &Features::ActorSummon::usePlayerRotation);

			ImGui::BeginDisabled(Features::ActorSummon::usePlayerScale);
			ImGui::Text("Scale:   ");
			ImGui::SameLine();
			ImGui::InputFloat3("##Actors##Summon##Scale", Features::ActorSummon::scale);
			ImGui::EndDisabled();
			ImGui::SameLine();
			ImGui::Checkbox("Use Player Scale##Actors##Summon", &Features::ActorSummon::usePlayerScale);

			ImGui::NewLine();

			if (ImGui::Button("Summon##ActorSpawn"))
			{
				SDK::FVector location = { Features::ActorSummon::location[0], Features::ActorSummon::location[1], Features::ActorSummon::location[2] };
				SDK::FRotator rotation = { Features::ActorSummon::rotation[0], Features::ActorSummon::rotation[1], Features::ActorSummon::rotation[2] };
				SDK::FVector scale = { Features::ActorSummon::scale[0], Features::ActorSummon::scale[1], Features::ActorSummon::scale[2] };

				if (Features::ActorSummon::usePlayerLocation || Features::ActorSummon::usePlayerRotation || Features::ActorSummon::usePlayerScale)
				{
					Unreal::Transform playerTransform = Unreal::PlayerController::GetTransform(0);

					if (Features::ActorSummon::usePlayerLocation)
						location = playerTransform.location;

					if (Features::ActorSummon::usePlayerRotation)
						rotation = playerTransform.rotation;

					if (Features::ActorSummon::usePlayerScale)
						scale = playerTransform.scale;
				}

				Unreal::Transform transform = { location, rotation, scale };

				std::vector<std::wstring> actorPathCollection = Utilities::String::Split(Features::ActorSummon::pathBuffer, L'|');
				if (actorPathCollection.size() > 0)
				{
					bool anyActorSpawned = false;

					for (std::wstring& actorPath : actorPathCollection) // <-- Reference!
					{
						std::wstring normalizedPath = Unreal::Object::NormalizeObjectPath(actorPath);

						bool wasSuccessfull = Unreal::Actor::SoftSummon(normalizedPath, transform) || Unreal::StaticMeshActor::SoftSummon(normalizedPath, transform) || Unreal::SkeletalMeshActor::SoftSummon(normalizedPath, transform);
						if (wasSuccessfull)
							anyActorSpawned = true;
					}

					GUI::PlayActionSound(anyActorSpawned);
				}
			}
#endif

			ImGui::CategorySeparator();
			ImGui::TreePop();
		}

		ImGui::NewLine();

		if (ImGui::Button("Update##Actors"))
		{
			Features::ActorsList::Update();
			Features::ActorsList::Filter();
			GUI::PlayActionSound(true);
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		if (ImGui::InputText("Search Filter##Actors", Features::ActorsList::filterBuffer, Features::ActorsList::filterBufferSize))
		{
			Features::ActorsList::Filter();
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		if (ImGui::Checkbox("Case Sensitive##Actors", &Features::ActorsList::filterCaseSensitive))
		{
			Features::ActorsList::Filter();
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		if (ImGui::ObjectFilterModeComboBox("##Actors", &Features::ActorsList::filterMode))
		{
			Features::ActorsList::Filter();
		}

#ifdef COLLISION_VISUALIZER
		ImGui::Checkbox("Draw Collision##Actors", &Features::CollisionVisualizer::enabled);
		ImGui::SameLine();
		if (ImGui::Button("*##CollisionVisualizer"))
		{
			ImGui::OpenPopup("CollisionVisualizer");
		}
		if (ImGui::BeginPopup("CollisionVisualizer"))
		{
			ImGui::TitleText("Colors");

			if (ImGui::ColorConfig4("Static Mesh        ", Features::CollisionVisualizer::color_StaticMesh))
			{
				Features::Config::Save();
			}

			if (ImGui::ColorConfig4("Primitive          ", Features::CollisionVisualizer::color_Primitive))
			{
				Features::Config::Save();
			}

			if (ImGui::ColorConfig4("Physics Volume     ", Features::CollisionVisualizer::color_PhysicsVolume))
			{
				Features::Config::Save();
			}

			if (ImGui::ColorConfig4("Blocking Volume    ", Features::CollisionVisualizer::color_BlockingVolume))
			{
				Features::Config::Save();
			}

			if (ImGui::ColorConfig4("Trigger Volume     ", Features::CollisionVisualizer::color_TriggerVolume))
			{
				Features::Config::Save();
			}

			if (ImGui::ColorConfig4("Post Porcess Volume", Features::CollisionVisualizer::color_PostProcessVolume))
			{
				Features::Config::Save();
			}

			if (ImGui::ColorConfig4("Other              ", Features::CollisionVisualizer::color_Other))
			{
				Features::Config::Save();
			}

			ImGui::Separator();

			ImGui::TitleText("Settings");

			ImGui::Text("Line Thickness:");
			ImGui::SameLine();
			if (ImGui::InputFloat("##LineThickness", &Features::CollisionVisualizer::thickness, 0.1f, 1.0f))
			{
				if (Features::CollisionVisualizer::thickness < 1.0f)
					Features::CollisionVisualizer::thickness = 1.0f;

				Features::Config::Save();
			}

			ImGui::EndPopup();
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
#endif

		ImGui::Checkbox("Enable Tracking##Actors", &Features::ActorsTracker::enabled);
		ImGui::SameLine();
		if (ImGui::Button("*##ActorsTracking"))
		{
			ImGui::OpenPopup("ActorsTracking");
		}
		if (ImGui::BeginPopup("ActorsTracking"))
		{
			ImGui::SetFontSmall();
			ImGui::Text("Draws circle at Actor root location alongside its technical name.\n\nExtremely helpful to locate an Actor within the world.");
			ImGui::SetFontRegular();

			ImGui::Separator();

			ImGui::TitleText("Colors");
			if (ImGui::ColorConfig4("Actor: ", Features::ActorsTracker::actorColor))
			{
				Features::Config::Save();
			}

			ImGui::Separator();

			ImGui::TitleText("Settings");
			if (ImGui::Checkbox("Show Distance", &Features::ActorsTracker::showDistance))
			{
				Features::Config::Save();
			}

			if (ImGui::Checkbox("Fade on Closeup", &Features::ActorsTracker::fadeOnCloseup))
			{
				Features::Config::Save();
			}

			ImGui::EndPopup();
		} 
		
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();

		ImGui::Text("In Distance:");
		ImGui::SameLine();
		if (ImGui::InputFloat("##FilterDistance##Actors", &Features::ActorsList::filterDistance, 1.0f, 10.0f, "%.1f"))
		{
			if (Features::ActorsList::filterDistance < 0.0f)
				Features::ActorsList::filterDistance = 0.0f;

			Features::ActorsList::Filter();
		}
		ImGui::SameLine();
		static const std::string distanceHint = std::format("Determines maximum distance from Player in metres.\n\n1m = {:.0f}units", Math::Metre_ToUnit(1.0f));
		ImGui::QuestionMarkHint(distanceHint.c_str());

		ImGui::KeyBindingInput("Update & Re-Filter Actors List:", &Inputs::Keybindings::debug_ActorsListUpdate);
		ImGui::SameLine();
		ImGui::QuestionMarkHint("Can be found useful when tracking/drawing while filtering Actors In Distance, allowing to update dataset w/o opening the menu.");

		ImGui::KeyBindingInput("Toggle Actors Tracking:        ", &Inputs::Keybindings::debug_ActorsListTracking);

#ifdef COLLISION_VISUALIZER
		ImGui::KeyBindingInput("Toggle Collision Draw:         ", &Inputs::Keybindings::debug_ActorsListCollisionDraw);
#endif

		ImGui::NewLine();

		if (ImGui::Button("Enable Collision (All)##Actors"))
		{
			bool anyActorCollisionEnabled = false;
			for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
			{
				if (actor.reference)
				{
					actor.reference->SetActorEnableCollision(true);
					anyActorCollisionEnabled = true;
				}
			}

			if (anyActorCollisionEnabled)
				Features::ActorsList::Update();

			GUI::PlayActionSound(anyActorCollisionEnabled);
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		if (ImGui::Button("Disable Collision (All)##Actors"))
		{
			bool anyActorCollisionDisabled = false;
			for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
			{
				if (actor.reference)
				{
					actor.reference->SetActorEnableCollision(false);
					anyActorCollisionDisabled = true;
				}
			}

			if (anyActorCollisionDisabled)
				Features::ActorsList::Update();

			GUI::PlayActionSound(anyActorCollisionDisabled);
		}

		if (ImGui::Button("Set Visible (All)##Actors"))
		{
			bool anyActorShown = false;
			for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
			{
				if (actor.reference)
				{
					Unreal::Actor::SetIsVisible(actor.reference, true);
					anyActorShown = true;
				}
			}

			if (anyActorShown)
				Features::ActorsList::Update();

			GUI::PlayActionSound(anyActorShown);
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		if (ImGui::Button("Set Hidden (All)##Actors"))
		{
			bool anyActorHidden = false;
			for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
			{
				if (actor.reference)
				{
					Unreal::Actor::SetIsVisible(actor.reference, false);
					anyActorHidden = true;
				}
			}

			if (anyActorHidden)
				Features::ActorsList::Update();

			GUI::PlayActionSound(anyActorHidden);
		}

		if (ImGui::Button("Destroy (All)##Actors"))
		{
			bool anyActorDestroyed = false;
			for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
			{
				if (actor.reference)
				{
					if (Unreal::Actor::Destroy(actor.reference))
						anyActorDestroyed = true;
				}
			}

			if (anyActorDestroyed)
				Features::ActorsList::Update();

			GUI::PlayActionSound(anyActorDestroyed);
		}

		ImGui::NewLine();

		/* Output to user interface Actors that are matching "Search Filter". */
		ImGui::PaginatedList("ActorsList", &Features::ActorsList::currentPage, Features::ActorsList::filteredActors, Features::ActorsList::rowsPerPage, [](Unreal::Actor::DataStructure& actor)
		{
			bool isValid = Unreal::Actor::IsValid(actor.reference);

			ImGui::PushStyleColor(ImGuiCol_Text, isValid ? ImGui::Color::Green : ImGui::Color::Red);
			bool isTreeNodeOpen = ImGui::TreeNode(actor.objectName.c_str());
			ImGui::PopStyleColor();

			if (isTreeNodeOpen)
			{
				ImGui::PushID(actor.objectName.c_str());

				ImGui::BeginDisabled(std::strcmp(Features::ActorsList::filterBuffer, actor.objectName.c_str()) == 0);
				if (ImGui::Button("Focus On"))
				{
					std::snprintf(Features::ActorsList::filterBuffer, sizeof(Features::ActorsList::filterBuffer), actor.objectName.c_str());
					Features::ActorsList::filterMode = ImGui::E_ObjectFilterMode::ObjectName;

					GUI::PlayActionSound(true);
				}
				ImGui::EndDisabled();
				ImGui::SameLine();
				ImGui::BeginDisabled(isValid == false);
				if (ImGui::Button("Refresh"))
				{
					Features::ActorsList::Update(actor);
					GUI::PlayActionSound(true);
				}
				ImGui::EndDisabled();

				ImGui::NewLine();

				ImGui::TextCopyable("Actor Class: %s", actor.className.c_str());
				if (ImGui::TreeNode("Class Hierarchy"))
				{
					Templates::ClassHierarchy::Draw(actor.superClassesNames);
					ImGui::TreePop();
				}
				ImGui::TextCopyable("Actor Object: %s", actor.objectName.c_str());

				ImGui::NewLine();

				ImGui::TextVectorColored("Cached Location: ", actor.transform.location);
				ImGui::TextRotatorColored("Cached Rotation: ", actor.transform.rotation);
				ImGui::TextVectorColored("Cached Scale:    ", actor.transform.scale);
				if (isValid)
				{
					Templates::LocationRotationScale::Draw(actor.reference);
				}

				ImGui::NewLine();

				if (ImGui::Button(isValid ? "Player -> Actor" : "Teleport To Location"))
				{
					SDK::ACharacter* character = Unreal::Character::Get();
					if (character)
					{
						bool wasSuccessfull = Unreal::Actor::TeleportTo(character, actor.transform.location);
						GUI::PlayActionSound(wasSuccessfull);
					}
					else
						GUI::PlayActionSound(false);
				}

				if (isValid)
				{
					ImGui::SameLine();
					if (ImGui::Button("Actor -> Player"))
					{
						SDK::FVector location = Unreal::PlayerController::GetLocation(0);

						bool wasSuccessfull = Unreal::Actor::TeleportTo(actor.reference, location);
						GUI::PlayActionSound(wasSuccessfull);
					}

					ImGui::NewLine();

					SDK::EComponentMobility actorMobility = Unreal::Actor::GetMobility(actor.reference);
					std::string mobility;
					switch (actorMobility)
					{
						case SDK::EComponentMobility::Static:
							mobility = "Static";
							break;

						case SDK::EComponentMobility::Stationary:
							mobility = "Stationary";
							break;

						case SDK::EComponentMobility::Movable:
							mobility = "Movable";
							break;

						default:
							mobility = std::to_string(static_cast<uint8_t>(actorMobility));
							break;
					}
					ImGui::Text("Mobility: %s", mobility);
					ImGui::SameLine();
					ImGui::QuestionMarkHint("Static - Never moves and relies entirely on baked lightmaps and shadows for lighting.\nLowest performance cost, ideal for architecture and environment pieces.\n\nStationary - Cannot move but allows changes to materials and visibility, and combines baked lighting with some dynamic shadow interactions.\nSlightly higher cost than Static, good for objects that stay in place but need minor runtime variations.\n\nMovable - Can move, rotate, scale, or animate and uses fully dynamic lighting and shadows.\nHighest performance cost, suited for characters, doors, vehicles, and interactive gameplay objects.");

					if (ImGui::Button("Make Static"))
					{
						bool wasSuccessfull = Unreal::Actor::MakeStatic(actor.reference);
						GUI::PlayActionSound(wasSuccessfull);
					}
					ImGui::SameLine();
					if (ImGui::Button("Make Stationary"))
					{
						bool wasSuccessfull = Unreal::Actor::MakeStationary(actor.reference);
						GUI::PlayActionSound(wasSuccessfull);
					}
					ImGui::SameLine();
					if (ImGui::Button("Make Movable"))
					{
						bool wasSuccessfull = Unreal::Actor::MakeMovable(actor.reference);
						GUI::PlayActionSound(wasSuccessfull);
					}

					ImGui::NewLine();

					ImGui::TextBoolColored("Has Collision:", Unreal::Actor::GetIsCollisionEnabled(actor.reference));
					if (ImGui::Button("Enable"))
					{
						bool wasSuccessfull = Unreal::Actor::SetIsCollisionEnabled(actor.reference, true);
						GUI::PlayActionSound(wasSuccessfull);
					}
					ImGui::SameLine();
					if (ImGui::Button("Disable"))
					{
						bool wasSuccessfull = Unreal::Actor::SetIsCollisionEnabled(actor.reference, false);
						GUI::PlayActionSound(wasSuccessfull);
					}

					ImGui::NewLine();

					ImGui::TextBoolColored("Is Visible:", Unreal::Actor::GetIsVisible(actor.reference));
					if (ImGui::Button("Show"))
					{
						bool wasSuccessfull = Unreal::Actor::SetIsVisible(actor.reference, true);
						GUI::PlayActionSound(wasSuccessfull);
					}
					ImGui::SameLine();
					if (ImGui::Button("Hide"))
					{
						bool wasSuccessfull = Unreal::Actor::SetIsVisible(actor.reference, false);
						GUI::PlayActionSound(wasSuccessfull);
					}

					ImGui::NewLine();

					ImGui::Text("Custom Time Dilation");
					ImGui::SliderFloatEditable("##CustomTimeDilation", &actor.reference->CustomTimeDilation, 0.0f, 10.0f);

					ImGui::NewLine();

					ImGui::TitleText("View Target");

					ImGui::Text("Blend Time");
					ImGui::SliderFloatEditable("##ViewTargetBlendTime", &Features::ActorsList::viewTargetBlendTime, 0.001f, 60.0f);

					ImGui::NewLine();

					ImGui::Text("Blend Exponent");
					ImGui::SliderFloatEditable("##ViewTargetBlendExponent", &Features::ActorsList::viewTargetBlendExponent, 0.001f, 60.0f);

					ImGui::NewLine();

					if (ImGui::Button("Linear"))
					{
						bool wasSuccessfull = Unreal::PlayerController::SetViewTarget(actor.reference, SDK::EViewTargetBlendFunction::VTBlend_Linear, Features::ActorsList::viewTargetBlendTime, Features::ActorsList::viewTargetBlendExponent);
						GUI::PlayActionSound(wasSuccessfull);
					}
					ImGui::SameLine();
					if (ImGui::Button("Cubic"))
					{
						bool wasSuccessfull = Unreal::PlayerController::SetViewTarget(actor.reference, SDK::EViewTargetBlendFunction::VTBlend_Cubic, Features::ActorsList::viewTargetBlendTime, Features::ActorsList::viewTargetBlendExponent);
						GUI::PlayActionSound(wasSuccessfull);
					}

					ImGui::NewLine();

					ImGui::TitleText("Attachment");
					ImGui::TextCopyable("Actor To Attach: %s", Features::ActorsList::actorToAttach.reference ? Features::ActorsList::actorToAttach.objectName.c_str() : "None");
					ImGui::TextCopyable("Attach Actor To: %s", actor.objectName.c_str());

					ImGui::NewLine();

					if (Features::ActorsList::actorToAttach.reference)
					{
						ImGui::BeginDisabled(actor.reference == Features::ActorsList::actorToAttach.reference);
						ImGui::PushStyleColor(ImGuiCol_Button, ImGui::LinearColor::Green);
						if (ImGui::Button("Attach To This Actor"))
						{
							if (actor.reference)
							{
								Unreal::Actor::AttachTo(Features::ActorsList::actorToAttach.reference, actor.reference);
								Features::ActorsList::actorToAttach = {};
								GUI::PlayActionSound(true);
							}
							else
								GUI::PlayActionSound(false);
						}
						ImGui::PopStyleColor();
						ImGui::EndDisabled();
						ImGui::SameLine();
						ImGui::PushStyleColor(ImGuiCol_Button, ImGui::LinearColor::Red);
						if (ImGui::Button("Cancel"))
						{
							Features::ActorsList::actorToAttach = {};
							GUI::PlayActionSound(true);
						}
						ImGui::PopStyleColor();
					}
					else
					{
						if (ImGui::Button("Select"))
						{
							if (actor.reference)
							{
								Features::ActorsList::actorToAttach = actor;
								GUI::PlayActionSound(true);
							}
							else
								GUI::PlayActionSound(false);
						}
					}

					ImGui::NewLine();

					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::Color::Red);
					if (ImGui::Button("Destroy"))
					{
						if (Unreal::Actor::Destroy(actor.reference))
						{
							Features::ActorsList::Update(actor);
							GUI::PlayActionSound(true);
						}
						else
							GUI::PlayActionSound(false);
					}
					ImGui::PopStyleColor();

#ifdef SOFT_PATH
					ImGui::NewLine();

					ImGui::TitleText("Material");
					ImGui::SmallText("Create dynamic Material Instance and apply it on Actor.");

					if (ImGui::TreeNode("Details##Material"))
					{
						ImGui::Text("Material Path");
						ImGui::InputText("##Material##Path", Features::ActorMaterial::materialInstancePathBuffer, Features::ActorMaterial::materialInstancePathBufferSize);

						ImGui::Text("Material Slot");
						ImGui::SliderInt("##Material##Slot", &Features::ActorMaterial::materialSlot, 0, 16);
						ImGui::SameLine();
						ImGui::Checkbox("All", &Features::ActorMaterial::useAllMaterialSlots);

						ImGui::NewLine();

						if (ImGui::Button("Create##Material"))
						{
							std::wstring materialPath = Utilities::String::ToWString(Features::ActorMaterial::materialInstancePathBuffer);
							std::wstring normalizedPath = Unreal::Object::NormalizeObjectPath(materialPath);

							bool wasSuccessfull = false;
							if (Features::ActorMaterial::useAllMaterialSlots)
								wasSuccessfull = Unreal::Actor::SetMaterial(actor.reference, normalizedPath);
							else
								wasSuccessfull = Unreal::Actor::SetMaterial(actor.reference, normalizedPath, Features::ActorMaterial::materialSlot);

							GUI::PlayActionSound(wasSuccessfull);
						}

						ImGui::TreePop();
					}
#endif

					if (actor.kind != Unreal::Actor::E_ActorKind::General)
					{
						ImGui::NewLine();

						Templates::Menus::Debug::Sub_Actors_Kind(actor);
					}

					ImGui::NewLine();

					Templates::Functions::Draw(actor.reference);

					ImGui::NewLine();

					Templates::Menus::Debug::Sub_Actors_Components(actor);
				}

				ImGui::NewLine();
				ImGui::PopID();
				ImGui::TreePop();
			}
		});
	}
}

void Templates::Menus::Debug::Sub_Actors_ThreadSafe()
{
	__try
	{
		Templates::Menus::Debug::Sub_Actors();
	}
	__except (EXCEPTION())
	{
		ImGui::PopID();

		ImGui::TitleText("Something Isn't Right!");
		ImGui::Text("Consider updating the Actors list.");
	}
}

void Templates::Menus::Debug::Sub_Actors_Kind(const Unreal::Actor::DataStructure& actor)
{
	switch (actor.kind)
	{
		case Unreal::Actor::E_ActorKind::PointLight:
		case Unreal::Actor::E_ActorKind::SpotLight:
		case Unreal::Actor::E_ActorKind::RectLight:
		case Unreal::Actor::E_ActorKind::DirectionalLight:
			if (SDK::ALight* light = static_cast<SDK::ALight*>(actor.reference))
			{
				SDK::ULightComponent* lightComponent = light->LightComponent;

				auto RefreshLightComponent = [](SDK::ULightComponent* lightComponent)
					{
						if (lightComponent)
						{
							if (lightComponent->IsVisible())
							{
								lightComponent->SetVisibility(false, false);
								lightComponent->SetVisibility(true, false);
							}
							else
							{
								lightComponent->SetVisibility(true, false);
								lightComponent->SetVisibility(false, false);
							}
						}
					};

				ImGui::TitleText("Light Settings");

				ImGui::BeginDisabled(lightComponent == nullptr);
				if (ImGui::TreeNode("Details##LightSettings"))
				{
					ImGui::TextBoolColored("Cast Shadows:", lightComponent->CastShadows);
					if (ImGui::Button("Enable##CastShadows"))
					{
						lightComponent->CastShadows = true;
						RefreshLightComponent(lightComponent);
						GUI::PlayActionSound(true);
					}
					ImGui::SameLine();
					if (ImGui::Button("Disable##CastShadows"))
					{
						lightComponent->CastShadows = false;
						RefreshLightComponent(lightComponent);
						GUI::PlayActionSound(true);
					}

					ImGui::NewLine();

					ImGui::TextBoolColored("Cast Static Shadows:", lightComponent->CastStaticShadows);
					if (ImGui::Button("Enable##CastStaticShadows"))
					{
						lightComponent->CastStaticShadows = true;
						RefreshLightComponent(lightComponent);
						GUI::PlayActionSound(true);
					}
					ImGui::SameLine();
					if (ImGui::Button("Disable##CastStaticShadows"))
					{
						lightComponent->CastStaticShadows = false;
						RefreshLightComponent(lightComponent);
						GUI::PlayActionSound(true);
					}

					ImGui::NewLine();

					ImGui::TextBoolColored("Cast Translucent Shadows:", lightComponent->CastTranslucentShadows);
					if (ImGui::Button("Enable##CastTranslucentShadows"))
					{
						lightComponent->CastTranslucentShadows = true;
						RefreshLightComponent(lightComponent);
						GUI::PlayActionSound(true);
					}
					ImGui::SameLine();
					if (ImGui::Button("Disable##CastTranslucentShadows"))
					{
						lightComponent->CastTranslucentShadows = false;
						RefreshLightComponent(lightComponent);
						GUI::PlayActionSound(true);
					}

					ImGui::NewLine();

					ImGui::TextBoolColored("Cast Volumetric Shadow:", lightComponent->bCastVolumetricShadow);
					if (ImGui::Button("Enable##CastVolumetricShadow"))
					{
						lightComponent->bCastVolumetricShadow = true;
						RefreshLightComponent(lightComponent);
						GUI::PlayActionSound(true);
					}
					ImGui::SameLine();
					if (ImGui::Button("Disable##CastVolumetricShadow"))
					{
						lightComponent->bCastVolumetricShadow = false;
						RefreshLightComponent(lightComponent);
						GUI::PlayActionSound(true);
					}

					ImGui::NewLine();

					/*
						bCastDeepShadow isn't member of LightComponent in older versions of the Engine (e.g. 4.22.3).
						Comment out following section of the code.
					*/
					ImGui::TextBoolColored("Cast Deep Shadow:", lightComponent->bCastDeepShadow);
					if (ImGui::Button("Enable##CastDeepShadow"))
					{
						lightComponent->bCastDeepShadow = true;
						RefreshLightComponent(lightComponent);
						GUI::PlayActionSound(true);
					}
					ImGui::SameLine();
					if (ImGui::Button("Disable##CastDeepShadow"))
					{
						lightComponent->bCastDeepShadow = false;
						RefreshLightComponent(lightComponent);
						GUI::PlayActionSound(true);
					}

					ImGui::NewLine();

					ImGui::TextBoolColored("Cast Raytraced Shadow:", lightComponent->bCastRaytracedShadow);
					if (ImGui::Button("Enable##CastRaytracedShadow"))
					{
						lightComponent->bCastRaytracedShadow = true;
						RefreshLightComponent(lightComponent);
						GUI::PlayActionSound(true);
					}
					ImGui::SameLine();
					if (ImGui::Button("Disable##CastRaytracedShadow"))
					{
						lightComponent->bCastRaytracedShadow = false;
						RefreshLightComponent(lightComponent);
						GUI::PlayActionSound(true);
					}

					ImGui::NewLine();

					ImGui::TextBoolColored("Use Raytraced Distance Shadows:", lightComponent->bUseRayTracedDistanceFieldShadows);
					if (ImGui::Button("Enable##UseRaytracedDistanceFieldShadows"))
					{
						lightComponent->bUseRayTracedDistanceFieldShadows = true;
						RefreshLightComponent(lightComponent);
						GUI::PlayActionSound(true);
					}
					ImGui::SameLine();
					if (ImGui::Button("Disable##UseRaytracedDistanceFieldShadows"))
					{
						lightComponent->bUseRayTracedDistanceFieldShadows = false;
						RefreshLightComponent(lightComponent);
						GUI::PlayActionSound(true);
					}

					ImGui::NewLine();

					ImGui::Text("Light Color");
					float lightColor[4] =
					{
						lightComponent->LightColor.R / 255.0f,
						lightComponent->LightColor.G / 255.0f,
						lightComponent->LightColor.B / 255.0f,
						lightComponent->LightColor.A / 255.0f,
					};

					if (ImGui::ColorPicker4("##LightColor", lightColor))
					{
						SDK::FLinearColor linearColor =
						{
							lightColor[0],
							lightColor[1],
							lightColor[2],
							lightColor[3]
						};

						lightComponent->SetLightColor(linearColor, false);
					}

					ImGui::NewLine();

					ImGui::Text("Intensity");
					ImGui::SliderFloatEditable("##Intensity", &lightComponent->Intensity, 0.0f, 1000000.0f);
					if (ImGui::IsItemDeactivatedAfterEdit())
					{
						RefreshLightComponent(lightComponent);
					}

					ImGui::NewLine();

					ImGui::Text("Draw Distance");
					ImGui::SliderFloatEditable("##DrawDistance", &lightComponent->MaxDrawDistance, 0.0f, 100000.0f);
					if (ImGui::IsItemDeactivatedAfterEdit())
					{
						RefreshLightComponent(lightComponent);
					}

					ImGui::NewLine();

					ImGui::Text("Light Function Fade Distance");
					ImGui::SliderFloatEditable("##LightFunctionFadeDistance: ", &lightComponent->LightFunctionFadeDistance, 0.0f, 100000.0f);
					if (ImGui::IsItemDeactivatedAfterEdit())
					{
						RefreshLightComponent(lightComponent);
					}

					ImGui::NewLine();

					ImGui::Text("Max Distance Fade Range");
					ImGui::SliderFloatEditable("##MaxDistanceFadeRange: ", &lightComponent->MaxDistanceFadeRange, 0.0f, 100000.0f);
					if (ImGui::IsItemDeactivatedAfterEdit())
					{
						RefreshLightComponent(lightComponent);
					}

					if (lightComponent->IsA(SDK::ULocalLightComponent::StaticClass()))
					{
						SDK::ULocalLightComponent* localLightComponent = static_cast<SDK::ULocalLightComponent*>(lightComponent);

						ImGui::NewLine();

						ImGui::Text("Attenuation Radius");
						ImGui::SliderFloatEditable("##AttenuationRadius", &localLightComponent->AttenuationRadius, 0.0f, 100000.0f);
						if (ImGui::IsItemDeactivatedAfterEdit())
						{
							RefreshLightComponent(lightComponent);
						}
					}

					if (actor.kind == Unreal::Actor::E_ActorKind::PointLight)
					{
						SDK::APointLight* pointLight = static_cast<SDK::APointLight*>(light);
						if (SDK::UPointLightComponent* pointLightComponent = pointLight->PointLightComponent)
						{
							ImGui::NewLine();

							ImGui::Text("Source Radius");
							ImGui::SliderFloatEditable("##SourceRadius", &pointLightComponent->SourceRadius, 0.0f, 1000.0f);
							if (ImGui::IsItemDeactivatedAfterEdit())
							{
								RefreshLightComponent(lightComponent);
							}

							ImGui::NewLine();

							ImGui::Text("Soft Source Radius");
							ImGui::SliderFloatEditable("##SoftSourceRadius", &pointLightComponent->SoftSourceRadius, 0.0f, 1000.0f);
							if (ImGui::IsItemDeactivatedAfterEdit())
							{
								RefreshLightComponent(lightComponent);
							}
						}
					}

					if (actor.kind == Unreal::Actor::E_ActorKind::SpotLight)
					{
						SDK::ASpotLight* spotLight = static_cast<SDK::ASpotLight*>(light);
						if (SDK::USpotLightComponent* spotLightComponent = spotLight->SpotLightComponent)
						{
							ImGui::NewLine();

							ImGui::Text("Inner Cone Angle");
							ImGui::SliderFloatEditable("##InnerConeAngle", &spotLightComponent->InnerConeAngle, 0.0f, 90.0f);
							if (ImGui::IsItemDeactivatedAfterEdit())
							{
								RefreshLightComponent(lightComponent);
							}

							ImGui::NewLine();

							ImGui::Text("Outer Cone Angle");
							ImGui::SliderFloatEditable("##OuterConeAngle", &spotLightComponent->OuterConeAngle, 0.0f, 90.0f);
							if (ImGui::IsItemDeactivatedAfterEdit())
							{
								RefreshLightComponent(lightComponent);
							}
						}
					}

					if (actor.kind == Unreal::Actor::E_ActorKind::RectLight)
					{
						SDK::ARectLight* rectLight = static_cast<SDK::ARectLight*>(light);
						if (SDK::URectLightComponent* rectLightComponent = rectLight->RectLightComponent)
						{
							ImGui::NewLine();

							ImGui::Text("Source Width");
							ImGui::SliderFloatEditable("##SourceWidth", &rectLightComponent->SourceWidth, 0.0f, 3000.0f);
							if (ImGui::IsItemDeactivatedAfterEdit())
							{
								RefreshLightComponent(lightComponent);
							}

							ImGui::NewLine();

							ImGui::Text("Source Height");
							ImGui::SliderFloatEditable("##SourceHeight", &rectLightComponent->SourceHeight, 0.0f, 3000.0f);
							if (ImGui::IsItemDeactivatedAfterEdit())
							{
								RefreshLightComponent(lightComponent);
							}

							ImGui::NewLine();

							ImGui::Text("Barn Door Angle");
							ImGui::SliderFloatEditable("##BarnDoorAngle", &rectLightComponent->BarnDoorAngle, 0.0f, 90.0f);
							if (ImGui::IsItemDeactivatedAfterEdit())
							{
								RefreshLightComponent(lightComponent);
							}

							ImGui::NewLine();

							ImGui::Text("Barn Door Length");
							ImGui::SliderFloatEditable("##BarnDoorLength", &rectLightComponent->BarnDoorLength, 0.0f, 3000.0f);
							if (ImGui::IsItemDeactivatedAfterEdit())
							{
								RefreshLightComponent(lightComponent);
							}
						}
					}

					if (actor.kind == Unreal::Actor::E_ActorKind::DirectionalLight)
					{
						SDK::ADirectionalLight* directionalLight = static_cast<SDK::ADirectionalLight*>(light);
						if (SDK::UDirectionalLightComponent* directionalLightComponent = static_cast<SDK::UDirectionalLightComponent*>(lightComponent))
						{
							ImGui::NewLine();

							ImGui::Text("Light Source Angle");
							ImGui::SliderFloatEditable("##LightSourceAngle", &directionalLightComponent->LightSourceAngle, 0.0f, 90.0f);
							if (ImGui::IsItemDeactivatedAfterEdit())
							{
								RefreshLightComponent(lightComponent);
							}

							ImGui::NewLine();

							ImGui::Text("Light Source Soft Angle");
							ImGui::SliderFloatEditable("##LightSourceSoftAngle", &directionalLightComponent->LightSourceSoftAngle, 0.0f, 90.0f);
							if (ImGui::IsItemDeactivatedAfterEdit())
							{
								RefreshLightComponent(lightComponent);
							}
		
							ImGui::NewLine();

							ImGui::Text("Dynamic Shadow Distance (Movable)");
							ImGui::SliderFloatEditable("##DynamicShadowDistanceMovable", &directionalLightComponent->DynamicShadowDistanceMovableLight, 0.0f, 100000.0f);
							if (ImGui::IsItemDeactivatedAfterEdit())
							{
								RefreshLightComponent(lightComponent);
							}

							ImGui::NewLine();

							ImGui::Text("Dynamic Shadow Distance (Stationary)");
							ImGui::SliderFloatEditable("##DynamicShadowDistanceMovable", &directionalLightComponent->DynamicShadowDistanceStationaryLight, 0.0f, 100000.0f);
							if (ImGui::IsItemDeactivatedAfterEdit())
							{
								RefreshLightComponent(lightComponent);
							}
						}
					}

					ImGui::TreePop();
				}
				ImGui::EndDisabled();
			}
			break;

		case Unreal::Actor::E_ActorKind::SkyLight:
			if (SDK::ASkyLight* skyLight = static_cast<SDK::ASkyLight*>(actor.reference))
			{
				SDK::USkyLightComponent* skyLightComponent = skyLight->LightComponent;

				auto RefreshSkyLightComponent = [](SDK::USkyLightComponent* component)
					{
						if (component)
						{
							if (component->IsVisible())
							{
								component->SetVisibility(false, false);
								component->SetVisibility(true, false);
							}
							else
							{
								component->SetVisibility(true, false);
								component->SetVisibility(false, false);
							}
						}
					};

				ImGui::TitleText("Sky Light Settings");
				ImGui::BeginDisabled(skyLightComponent == nullptr);
				if (ImGui::TreeNode("Details##SkyLightSettings"))
				{
					ImGui::TextBoolColored("Cast Shadows:", skyLightComponent->CastShadows);
					if (ImGui::Button("Enable##SkyCastShadows"))
					{
						skyLightComponent->CastShadows = true;
						RefreshSkyLightComponent(skyLightComponent);
						GUI::PlayActionSound(true);
					}
					ImGui::SameLine();
					if (ImGui::Button("Disable##SkyCastShadows"))
					{
						skyLightComponent->CastShadows = false;
						RefreshSkyLightComponent(skyLightComponent);
						GUI::PlayActionSound(true);
					}

					ImGui::NewLine();

					ImGui::TextBoolColored("Cast Volumetric Shadow:", skyLightComponent->bCastVolumetricShadow);
					if (ImGui::Button("Enable##SkyCastVolumetricShadow"))
					{
						skyLightComponent->bCastVolumetricShadow = true;
						RefreshSkyLightComponent(skyLightComponent);
						GUI::PlayActionSound(true);
					}
					ImGui::SameLine();
					if (ImGui::Button("Disable##SkyCastVolumetricShadow"))
					{
						skyLightComponent->bCastVolumetricShadow = false;
						RefreshSkyLightComponent(skyLightComponent);
						GUI::PlayActionSound(true);
					}

					ImGui::NewLine();

					ImGui::Text("Light Color");
					float lightColor[4] =
					{
						skyLightComponent->LightColor.R / 255.0f,
						skyLightComponent->LightColor.G / 255.0f,
						skyLightComponent->LightColor.B / 255.0f,
						skyLightComponent->LightColor.A / 255.0f,
					};

					if (ImGui::ColorPicker4("##SkyLightColor", lightColor))
					{
						SDK::FLinearColor linearColor =
						{
							lightColor[0],
							lightColor[1],
							lightColor[2],
							lightColor[3]
						};

						skyLightComponent->SetLightColor(linearColor);
					}

					ImGui::NewLine();

					ImGui::Text("Intensity");
					ImGui::SliderFloatEditable("##SkyIntensity", &skyLightComponent->Intensity, 0.0f, 100.0f);
					if (ImGui::IsItemDeactivatedAfterEdit())
					{
						RefreshSkyLightComponent(skyLightComponent);
					}

					ImGui::NewLine();

					ImGui::Text("Volumetric Scattering Intensity");
					ImGui::SliderFloatEditable("##SkyVolumetricScattering", &skyLightComponent->VolumetricScatteringIntensity, 0.0f, 10.0f);
					if (ImGui::IsItemDeactivatedAfterEdit())
					{
						RefreshSkyLightComponent(skyLightComponent);
					}

					ImGui::TreePop();
				}
				ImGui::EndDisabled();
			}
			break;

		case Unreal::Actor::E_ActorKind::AtmosphericFog:
			if (SDK::AAtmosphericFog* atmosphericFog = static_cast<SDK::AAtmosphericFog*>(actor.reference))
			{
				if (SDK::UAtmosphericFogComponent* atmosphericFogComponent = atmosphericFog->AtmosphericFogComponent)
				{
					ImGui::TitleText("Atmospheric Fog Settings");
					if (ImGui::TreeNode("Details##AtmosphericFogSettings"))
					{
						ImGui::Text("Sun Multiplier");
						ImGui::SliderFloatEditable("##SunMultiplier", &atmosphericFogComponent->SunMultiplier, 0.0f, 100.0f);

						ImGui::Text("Fog Multiplier");
						ImGui::SliderFloatEditable("##FogMultiplier", &atmosphericFogComponent->FogMultiplier, 0.0f, 100.0f);

						ImGui::Text("Density Multiplier");
						ImGui::SliderFloatEditable("##DensityMultiplier", &atmosphericFogComponent->DensityMultiplier, 0.0f, 100.0f);

						ImGui::TreePop();
					}
				}
			}
			break;

		case Unreal::Actor::E_ActorKind::ExponentialHeightFog:
			if (SDK::AExponentialHeightFog* exponentialHeightFog = static_cast<SDK::AExponentialHeightFog*>(actor.reference))
			{
				if (SDK::UExponentialHeightFogComponent* exponentialHeightFogComponent = exponentialHeightFog->Component)
				{
					ImGui::TitleText("Exponential Height Fog Settings");
					if (ImGui::TreeNode("Details##ExponentialHeightFogSettings"))
					{
						ImGui::Text("Fog Density");
						ImGui::SliderFloatEditable("##Density", &exponentialHeightFogComponent->FogDensity, 0.0f, 10.0f);

						ImGui::Text("Fog Height Falloff");
						ImGui::SliderFloatEditable("##HeightFalloff", &exponentialHeightFogComponent->FogHeightFalloff, 0.0f, 10.0f);

						ImGui::Text("Fog Max Opacity");
						ImGui::SliderFloatEditable("##MaxOpacity", &exponentialHeightFogComponent->FogMaxOpacity, 0.0f, 1.0f);

						ImGui::Text("Start Distance");
						ImGui::SliderFloatEditable("##StartDist", &exponentialHeightFogComponent->StartDistance, 0.0f, 100000.0f);

						ImGui::NewLine();

						ImGui::TextBoolColored("Volumetric Fog:", exponentialHeightFogComponent->bEnableVolumetricFog);
						if (ImGui::Button("Enable##VolumetricFog"))
						{
							exponentialHeightFogComponent->bEnableVolumetricFog = true;
							GUI::PlayActionSound(true);
						}
						ImGui::SameLine();
						if (ImGui::Button("Disable##VolumetricFog"))
						{
							exponentialHeightFogComponent->bEnableVolumetricFog = false;
							GUI::PlayActionSound(true);
						}

						ImGui::TreePop();
					}
				}
			}
			break;

		case Unreal::Actor::E_ActorKind::Camera:
			if (SDK::ACameraActor* camera = static_cast<SDK::ACameraActor*>(actor.reference))
			{
				if (SDK::UCameraComponent* cameraComponent = camera->CameraComponent)
				{
					ImGui::TitleText("Camera Settings");
					if (ImGui::TreeNode("Details##CameraSettings"))
					{
						ImGui::Text("Field Of View");
						ImGui::SliderFloatEditable("##FOV", &cameraComponent->FieldOfView, 5.0f, 170.0f);

						ImGui::Text("Aspect Ratio");
						ImGui::SliderFloatEditable("##AspectRatio", &cameraComponent->AspectRatio, 0.1f, 5.0f);

						ImGui::NewLine();

						ImGui::TextBoolColored("Constrain Aspect Ratio:", cameraComponent->bConstrainAspectRatio);
						if (ImGui::Button("Enable##ConstrainAspectRatio"))
						{
							cameraComponent->bConstrainAspectRatio = true;
							GUI::PlayActionSound(true);
						}
						ImGui::SameLine();
						if (ImGui::Button("Disable##ConstrainAspectRatio"))
						{
							cameraComponent->bConstrainAspectRatio = false;
							GUI::PlayActionSound(true);
						}

						ImGui::TreePop();
					}
				}
			}
			break;

		case Unreal::Actor::E_ActorKind::Pawn:
			if (SDK::APawn* pawn = static_cast<SDK::APawn*>(actor.reference))
			{
#ifdef SOFT_PATH
				ImGui::TitleText("Animation");
				ImGui::SmallText("Dynamic Animation playing by soft path, for example \"/Game/Character/AnimAsset_Jump.AnimAsset_Jump\".");
				if (ImGui::TreeNode("Details##PawnAnimation"))
				{
					ImGui::TitleText("Montage");

					ImGui::Text("Montage Path");
					ImGui::InputText("##PawnAnimation##Montage", Features::PawnAnimation::animationMontagePathBuffer, Features::PawnAnimation::animationMontagePathBufferSize);

					ImGui::Text("Start At");
					ImGui::SliderFloatEditable("##PawnAnimation##Montage##StartAt", &Features::PawnAnimation::animationMontageStartAt, 0.0f, 60.0f);

					ImGui::Text("Play Rate");
					ImGui::SliderFloatEditable("##PawnAnimation##Montage##PlayRate", &Features::PawnAnimation::animationMontagePlayRate, 0.001f, 10.0f);

					if (ImGui::Button("Play##PawnAnimation##Montage"))
					{
						std::wstring assetPath = Utilities::String::ToWString(Features::PawnAnimation::animationPathBuffer);
						std::wstring normalizedPath = Unreal::Object::NormalizeObjectPath(assetPath);

						bool wasSuccessfull = Unreal::Pawn::PlayAnimationMontage(pawn, normalizedPath, Features::PawnAnimation::animationMontageStartAt, Features::PawnAnimation::animationMontagePlayRate, Features::PawnAnimation::animationMontageStopAllMontages);
						GUI::PlayActionSound(wasSuccessfull);
					}
					ImGui::SameLine();
					ImGui::Checkbox("Stop All Montages##PawnAnimation##Montage", &Features::PawnAnimation::animationMontageStopAllMontages);

					ImGui::NewLine();

					ImGui::TitleText("Asset");

					ImGui::Text("Animation Path");
					ImGui::InputText("##PawnAnimation##Asset", Features::PawnAnimation::animationPathBuffer, Features::PawnAnimation::animationPathBufferSize);

					if (ImGui::Button("Play##PawnAnimation##Asset"))
					{
						std::wstring assetPath = Utilities::String::ToWString(Features::PawnAnimation::animationPathBuffer);
						std::wstring normalizedPath = Unreal::Object::NormalizeObjectPath(assetPath);

						bool wasSuccessfull = Unreal::Pawn::PlayAnimation(pawn, normalizedPath.c_str(), Features::PawnAnimation::animationLooping);
						GUI::PlayActionSound(wasSuccessfull);
					}
					ImGui::SameLine();
					ImGui::Checkbox("Looping##PawnAnimation##Asset", &Features::PawnAnimation::animationLooping);

					ImGui::TreePop();
				}

				ImGui::NewLine();
#endif
		
				if (ImGui::Button("Possess"))
				{
					SDK::APlayerController* playerController = Unreal::PlayerController::Get();
					if (playerController && pawn)
					{
						playerController->Possess(pawn);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
			}
			break;

		case Unreal::Actor::E_ActorKind::Decal:
			if (SDK::ADecalActor* decal = static_cast<SDK::ADecalActor*>(actor.reference))
			{
				if (SDK::UDecalComponent* decalComponent = decal->Decal)
				{
					ImGui::TitleText("Decal Settings");
					if (ImGui::TreeNode("Details##DecalSettings"))
					{
						ImGui::Text("Fade Screen Size");
						ImGui::SliderFloatEditable("##FadeScreenSize", &decalComponent->FadeScreenSize, 0.0f, 1.0f);

						ImGui::Text("Sort Order");
						ImGui::SliderIntEditable("##SortOrder", &decalComponent->SortOrder, -100, 100);

						ImGui::TreePop();
					}
				}
			}
			break;

		case Unreal::Actor::E_ActorKind::TextRender:
			if (SDK::ATextRenderActor* textRenderActor = static_cast<SDK::ATextRenderActor*>(actor.reference))
			{
				ImGui::TitleText("Text");
				ImGui::BeginDisabled(textRenderActor->TextRender == nullptr);
				if (ImGui::TreeNode("Details##Text"))
				{
					if (SDK::UTextRenderComponent* textRenderComponent = textRenderActor->TextRender)
					{
						ImGui::Text("Content");

						static SDK::UTextRenderComponent* lastTextRenderContentSource = nullptr;
						static const size_t textRenderContentBufferSize = SIZE_BUFFER_POSITIONSENTRY;
						static char textRenderContentBuffer[textRenderContentBufferSize] = {};

						if (ImGui::Button("Get##Text##Content"))
						{
							if (textRenderComponent)
							{
								std::string content = textRenderComponent->Text.ToString();
								strcpy_s(textRenderContentBuffer, content.c_str());
								lastTextRenderContentSource = textRenderComponent;

								GUI::PlayActionSound(true);
							}
							else
								GUI::PlayActionSound(false);
						}
						ImGui::SameLine();
						if (textRenderComponent != lastTextRenderContentSource)
						{
							ImGui::PushStyleColor(ImGuiCol_Text, ImGui::Color::Red);
							ImGui::InputText("##Text##Content", textRenderContentBuffer, textRenderContentBufferSize);
							ImGui::PopStyleColor();
						}
						else
						{
							ImGui::InputText("##Text##Content", textRenderContentBuffer, textRenderContentBufferSize);
						}
						ImGui::SameLine();
						if (ImGui::Button("Set##Text##Content"))
						{
							if (textRenderComponent)
							{
								std::wstring content = Utilities::String::ToWString(textRenderContentBuffer);
								textRenderComponent->SetText(SDK::FString(content.c_str()));
								lastTextRenderContentSource = textRenderComponent;

								GUI::PlayActionSound(true);
							}
							else
								GUI::PlayActionSound(false);
						}

						ImGui::NewLine();

						ImGui::Text("World Size");
						ImGui::SliderFloatEditable("##Text##FontSize", &textRenderComponent->WorldSize, 1.0f, 64.0f);
						if (ImGui::IsItemDeactivatedAfterEdit())
						{
							textRenderComponent->SetWorldSize(textRenderComponent->WorldSize);
						}
					}
					else
						ImGui::Text("Text Render Component Doesn't Exist!");

					ImGui::TreePop();
				}

				ImGui::EndDisabled();
			}
			break;
	}
}

void Templates::Menus::Debug::Sub_Actors_Components(const Unreal::Actor::DataStructure& actor)
{
	ImGui::TitleText("Components");
	if (ImGui::TreeNode("Details##Components"))
	{
		ImGui::InputText("Search Filter##Components", Features::ActorsList::componentsFilterBuffer, Features::ActorsList::componentsFilterBufferSize);
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		ImGui::Checkbox("Case Sensitive##Components", &Features::ActorsList::componentsFilterCaseSensitive);
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		ImGui::ObjectFilterModeComboBox("##Components", &Features::ActorsList::componentsFilterMode);

		ImGui::NewLine();

		/* Filter Components by "Search Filter" */
		std::vector<Unreal::ActorComponent::DataStructure> filteredComponents;
		switch (Features::ActorsList::componentsFilterMode)
		{
			case ImGui::E_ObjectFilterMode::ClassName:
				filteredComponents = Unreal::ActorComponent::FilterByClassName(actor.components, Features::ActorsList::componentsFilterBuffer, Features::ActorsList::componentsFilterCaseSensitive);
				break;

			case ImGui::E_ObjectFilterMode::ObjectName:
				filteredComponents = Unreal::ActorComponent::FilterByObjectName(actor.components, Features::ActorsList::componentsFilterBuffer, Features::ActorsList::componentsFilterCaseSensitive);
				break;

			case ImGui::E_ObjectFilterMode::All:
				filteredComponents = Unreal::ActorComponent::FilterByClassAndObjectName(actor.components, Features::ActorsList::componentsFilterBuffer, Features::ActorsList::componentsFilterCaseSensitive);
				break;
		}

		for (Unreal::ActorComponent::DataStructure& component : filteredComponents) // <-- Reference!
		{
			if (ImGui::TreeNode(component.objectName.c_str()))
			{
				ImGui::TextCopyable("Component Class: %s", component.className.c_str());
				ImGui::TextCopyable("Component Object: %s", component.objectName.c_str());

				ImGui::NewLine();

				ImGui::TextBoolColored("Is Active:", component.reference->bIsActive);

				if (ImGui::Button("Enable"))
				{
					if (component.reference)
					{
						component.reference->Activate(false);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::SameLine();
				if (ImGui::Button("Disable"))
				{
					if (component.reference)
					{
						component.reference->Deactivate();
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::SameLine();
				if (ImGui::Button("Reset"))
				{
					if (component.reference)
					{
						component.reference->Activate(true);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}

				ImGui::NewLine();

				ImGui::TextBoolColored("Auto Activate:", component.reference->bAutoActivate);
				ImGui::TextBoolColored("Editor Only:", component.reference->bIsEditorOnly);

				ImGui::TextBoolColored("Net Addressible:", component.reference->bNetAddressable);
				ImGui::TextBoolColored("Replicates:", component.reference->bReplicates);

				ImGui::NewLine();

				std::string creationMethod;
				switch (component.reference->CreationMethod)
				{
					case SDK::EComponentCreationMethod::Native:
						creationMethod = "Native";
						break;

					case SDK::EComponentCreationMethod::SimpleConstructionScript:
						creationMethod = "Simple Contruction Script";
						break;

					case SDK::EComponentCreationMethod::UserConstructionScript:
						creationMethod = "User Construction Script";
						break;

					case SDK::EComponentCreationMethod::Instance:
						creationMethod = "Instance";
						break;

					default:
						creationMethod = std::to_string(static_cast<uint8_t>(component.reference->CreationMethod));
						break;
				}
				ImGui::Text("Creation Method: %s", creationMethod.c_str());

				ImGui::NewLine();

				Templates::Functions::Draw(component.reference);

				ImGui::NewLine();
				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}
}

void Templates::Menus::Debug::Sub_Widgets()
{
	ImGui::TitleText("Widgets");
	if (ImGui::CollapsingHeader("Details##Widgets"))
	{
#ifdef SOFT_PATH
		ImGui::TitleText("Construct");
		Templates::Descriptions::SoftPath::Draw("Widget", "/Game/Widgets/WBP_DebugMenu.WBP_DebugMenu_C");

		if (ImGui::TreeNode("Details##Widgets##Construct"))
		{
			ImGui::Text("Soft Path");
			ImGui::InputText("##Widgets##Construct##Path", Features::WidgetConstruct::pathBuffer, Features::WidgetConstruct::pathBufferSize);

			ImGui::NewLine();

			ImGui::Text("Z Order");
			ImGui::SliderIntEditable("##Widgets##Construct##ZOrder", &Features::WidgetConstruct::zOrder, 0, 100);

			ImGui::NewLine();

			if (ImGui::Button("Construct##Widgets##Construct"))
			{
				std::vector<std::wstring> widgetPathCollection = Utilities::String::Split(Features::WidgetConstruct::pathBuffer, L'|');
				if (widgetPathCollection.size() > 0)
				{
					bool anyWidgetConstructed = false;

					for (std::wstring& widgetPath : widgetPathCollection) // <-- Reference!
					{
						std::wstring normalizedPath = Unreal::Object::NormalizeObjectPath(widgetPath);
						if (SDK::UUserWidget* widgetReference = Unreal::UserWidget::SoftConstruct(normalizedPath))
						{
							widgetReference->AddToViewport(Features::WidgetConstruct::zOrder);
							anyWidgetConstructed = true;
						}
					}

					GUI::PlayActionSound(anyWidgetConstructed);
				}
				else
					GUI::PlayActionSound(false);
			}

			ImGui::CategorySeparator();
			ImGui::TreePop();
		}

		ImGui::NewLine();
#endif

		static float scaleFactor = 1.0;
		static bool scaleFactorObtained = false;
		if (scaleFactorObtained)
		{
			ImGui::Text("Scale Factor");
			ImGui::SliderFloatEditable("##Widgets##ScaleFactor", &scaleFactor, 0.001f, 2.000f);
			if (ImGui::IsItemDeactivatedAfterEdit())
			{
				Unreal::UserInterfaceSettings::SetApplicationScale(scaleFactor);
			}
		}
		else
		{
			scaleFactorObtained = Unreal::UserInterfaceSettings::GetApplicationScale(&scaleFactor);
		}

		ImGui::NewLine();

		if (ImGui::Button("Update##Widgets"))
		{
			Features::WidgetsList::Update();
			Features::WidgetsList::Filter();
			GUI::PlayActionSound(true);
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		if (ImGui::InputText("Search Filter##Widgets", Features::WidgetsList::filterBuffer, Features::WidgetsList::filterBufferSize))
		{
			Features::WidgetsList::Filter();
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		if (ImGui::Checkbox("Case Sensitive##Widgets", &Features::WidgetsList::filterCaseSensitive))
		{
			Features::WidgetsList::Filter();
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		if (ImGui::ObjectFilterModeComboBox("##Widgets", &Features::WidgetsList::filterMode))
		{
			Features::WidgetsList::Filter();
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		if (ImGui::Checkbox("Top Level Only##Widgets", &Features::WidgetsList::filterTopLevelOnly))
		{
			Features::WidgetsList::Filter();
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		if (ImGui::Checkbox("Rendered Only##Widgets", &Features::WidgetsList::filterRenderedOnly))
		{
			Features::WidgetsList::Filter();
		}

		ImGui::NewLine();

		ImGui::PaginatedList("WidgetsList", &Features::WidgetsList::currentPage, Features::WidgetsList::filteredWidgets, Features::WidgetsList::rowsPerPage, [](Unreal::UserWidget::DataStructure& widget)
		{
			bool isValid = Unreal::Object::IsValid(widget.reference);

			ImGui::PushStyleColor(ImGuiCol_Text, isValid ? ImGui::Color::Green : ImGui::Color::Red);
			bool isTreeNodeOpen = ImGui::TreeNode(widget.objectName.c_str());
			ImGui::PopStyleColor();

			if (isTreeNodeOpen)
			{
				ImGui::PushID(widget.objectName.c_str());

				ImGui::BeginDisabled(std::strcmp(Features::WidgetsList::filterBuffer, widget.objectName.c_str()) == 0);
				if (ImGui::Button("Focus On"))
				{
					std::snprintf(Features::WidgetsList::filterBuffer, sizeof(Features::WidgetsList::filterBuffer), widget.objectName.c_str());
					Features::WidgetsList::filterMode = ImGui::E_ObjectFilterMode::ObjectName;

					GUI::PlayActionSound(true);
				}
				ImGui::EndDisabled();
				ImGui::SameLine();
				if (ImGui::Button("Refresh"))
				{
					Features::WidgetsList::Update(widget);
					GUI::PlayActionSound(true);
				}

				ImGui::NewLine();

				ImGui::TextCopyable("Widget Class: %s", widget.className.c_str());
				if (ImGui::TreeNode("Class Hierarchy"))
				{
					Templates::ClassHierarchy::Draw(widget.superClassesNames);
					ImGui::TreePop();
				}
				ImGui::TextCopyable("Widget Object: %s", widget.objectName.c_str());

				if (isValid)
				{
					ImGui::NewLine();

					auto VisibilityStatus = [](SDK::UWidget* widgetReference)
					{
						std::string visibility;
						switch (widgetReference->Visibility)
						{
							case SDK::ESlateVisibility::Visible:
								visibility = "Visible";
								break;

							case SDK::ESlateVisibility::Collapsed:
								visibility = "Collapsed";
								break;

							case SDK::ESlateVisibility::Hidden:
								visibility = "Hidden";
								break;

							case SDK::ESlateVisibility::HitTestInvisible:
								visibility = "Hit Test Invisible";
								break;

							case SDK::ESlateVisibility::SelfHitTestInvisible:
								visibility = "Self Hit Test Invisible";
								break;

							default:
								visibility = std::to_string(static_cast<uint8_t>(SDK::ESlateVisibility::SelfHitTestInvisible));
								break;
						}
						ImGui::Text("Visibility: %s", visibility.c_str());
					};

					ImGui::TextBoolColored("Is Top Level:", widget.isTopLevel);
					ImGui::TextBoolColored("Is Rendered:", widget.isRendered);
					if (widget.parent.reference)
					{
						if (ImGui::TreeNode("Parent Widget"))
						{
							bool isParentValid = Unreal::Object::IsValid(widget.parent.reference);

							ImGui::TextCopyable("Widget Class: %s", widget.parent.className.c_str());
							if (ImGui::TreeNode("Class Hierarchy"))
							{
								Templates::ClassHierarchy::Draw(widget.parent.superClassesNames);
								ImGui::TreePop();
							}
							ImGui::TextCopyable("Widget Object: %s", widget.parent.objectName.c_str());

							if (isParentValid)
							{
								ImGui::NewLine();

								VisibilityStatus(widget.parent.reference);
							}
							
							ImGui::TreePop();
						}
					}

					if (widget.isRendered)
					{
						ImGui::NewLine();

						ImGui::TextCopyable("Position: X: %.3f Y: %.3f", widget.absolutePosition.X, widget.absolutePosition.Y);
						ImGui::TextCopyable("Size: X: %.3f Y: %.3f", widget.absoluteSize.X, widget.absoluteSize.Y);
					}

					ImGui::NewLine();

					VisibilityStatus(widget.reference);
					
					if (ImGui::Button("Make Visible"))
					{
						bool wasSuccessfull = Unreal::UserWidget::SetVisibility(widget.reference, SDK::ESlateVisibility::Visible);
						GUI::PlayActionSound(wasSuccessfull);
					}
					ImGui::SameLine();
					if (ImGui::Button("Make Hidden"))
					{
						bool wasSuccessfull = Unreal::UserWidget::SetVisibility(widget.reference, SDK::ESlateVisibility::Hidden);
						GUI::PlayActionSound(wasSuccessfull);
					}
					ImGui::SameLine();
					if (ImGui::Button("Make Collapsed"))
					{
						bool wasSuccessfull = Unreal::UserWidget::SetVisibility(widget.reference, SDK::ESlateVisibility::Collapsed);
						GUI::PlayActionSound(wasSuccessfull);
					}
					
					if (ImGui::Button("Make Hit Test Invisible"))
					{
						bool wasSuccessfull = Unreal::UserWidget::SetVisibility(widget.reference, SDK::ESlateVisibility::HitTestInvisible);
						GUI::PlayActionSound(wasSuccessfull);
					}
					ImGui::SameLine();
					if (ImGui::Button("Make Self Hit Test Invisible"))
					{
						bool wasSuccessfull = Unreal::UserWidget::SetVisibility(widget.reference, SDK::ESlateVisibility::SelfHitTestInvisible);
						GUI::PlayActionSound(wasSuccessfull);
					}

					if (widget.isRendered)
					{
						ImGui::NewLine();

						ImGui::TitleText("Visualisation");
						ImGui::SmallText("Draws Widget boundaries on screen.");
						if (ImGui::TreeNode("Details##WidgetVisualisation"))
						{
							ImGui::TextCopyable("Widget: %s", Features::WidgetVisualisation::widgetToVisualise.reference ? Features::WidgetVisualisation::widgetToVisualise.objectName.c_str() : "None");

							ImGui::NewLine();

							if (ImGui::ColorConfig4("Color##WidgetVisualisation", Features::WidgetVisualisation::color))
							{
								Features::Config::Save();
							}

							ImGui::NewLine();

							ImGui::Text("Line Thickness");
							if (ImGui::SliderFloatEditable("##WidgetVisualisation##LineThickness", &Features::WidgetVisualisation::lineThickness, 1.0f, 10.0f))
							{
								Features::Config::Save();
							}

							ImGui::NewLine();

							ImGui::BeginDisabled(Features::WidgetVisualisation::widgetToVisualise.reference == widget.reference);
							ImGui::PushStyleColor(ImGuiCol_Button, ImGui::Color::Green);
							if (ImGui::Button("Visualise Current"))
							{
								Features::WidgetVisualisation::widgetToVisualise = widget;
								GUI::PlayActionSound(true);
							}
							ImGui::PopStyleColor();
							ImGui::EndDisabled();
							ImGui::SameLine();
							ImGui::BeginDisabled(Features::WidgetVisualisation::widgetToVisualise.reference == nullptr);
							ImGui::PushStyleColor(ImGuiCol_Button, ImGui::Color::Red);
							if (ImGui::Button("Cancel"))
							{
								Features::WidgetVisualisation::widgetToVisualise = {};
								GUI::PlayActionSound(true);
							}
							ImGui::PopStyleColor();
							ImGui::EndDisabled();

							ImGui::TreePop();
						}
					}

					ImGui::NewLine();

					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::Color::Green);
					if (ImGui::Button("Add To Viewport"))
					{
						if (widget.reference)
						{
							widget.reference->AddToViewport(0);
							GUI::PlayActionSound(true);
						}
						else
							GUI::PlayActionSound(false);
					}
					ImGui::SameLine();
					if (ImGui::Button("Add To Player Screen"))
					{
						if (widget.reference)
						{
							widget.reference->AddToPlayerScreen(0);
							GUI::PlayActionSound(true);
						}
						else
							GUI::PlayActionSound(false);
					}
					ImGui::PopStyleColor();

					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::Color::Red);
					if (ImGui::Button("Remove From Parent"))
					{
						if (widget.reference)
						{
							widget.reference->RemoveFromParent();
							GUI::PlayActionSound(true);
						}
						else
							GUI::PlayActionSound(false);
					}
					ImGui::SameLine();
					if (ImGui::Button("Remove From Viewport"))
					{
						if (widget.reference)
						{
							widget.reference->RemoveFromViewport();
							GUI::PlayActionSound(true);
						}
						else
							GUI::PlayActionSound(false);
					}
					ImGui::PopStyleColor();

					ImGui::NewLine();

					Templates::Functions::Draw(widget.reference);
				}
				
				ImGui::NewLine();
				ImGui::PopID();
				ImGui::TreePop();
			}
		});
	}
}

void Templates::Menus::Debug::Sub_Widgets_ThreadSafe()
{
	__try
	{
		Templates::Menus::Debug::Sub_Widgets();
	}
	__except (EXCEPTION())
	{
		ImGui::PopID();

		ImGui::TitleText("Something Isn't Right!");
		ImGui::Text("Consider updating the Widgets list.");
	}
}

void Templates::Menus::Debug::Sub_Objects()
{
	ImGui::TitleText("Objects");
	if (ImGui::CollapsingHeader("Details##Objects"))
	{
#ifdef SOFT_PATH
		ImGui::TitleText("Construct");
		Templates::Descriptions::SoftPath::Draw("Object", "/Game/Subsystems/WeatherSubsystem.WeatherSubsystem");

		if (ImGui::TreeNode("Details##Objects##Construct"))
		{
			ImGui::Text("Soft Path");
			ImGui::InputText("##Objects##Construct##Path", Features::ObjectConstruct::pathBuffer, Features::ObjectConstruct::pathBufferSize);

			ImGui::NewLine();

			if (ImGui::Button("Construct##Objects##Construct"))
			{
				std::vector<std::wstring> objectPathCollection = Utilities::String::Split(Features::ObjectConstruct::pathBuffer, L'|');
				if (objectPathCollection.size() > 0)
				{
					bool anyObjectConstructed = false;

					for (std::wstring& objectPath : objectPathCollection) // <-- Reference!
					{
						std::wstring normalizedPath = Unreal::Object::NormalizeObjectPath(objectPath);
						if (SDK::UObject* objectReference = Unreal::Object::SoftLoadObject(normalizedPath))
						{
							SDK::UClass* objectClass = objectReference->Class;

							if (SDK::UObject* objectInstance = Unreal::Object::Construct(objectClass, objectReference))
							{
								anyObjectConstructed = true;
							}
						}
					}

					GUI::PlayActionSound(anyObjectConstructed);
				}
				else
					GUI::PlayActionSound(false);
			}

			ImGui::CategorySeparator();
			ImGui::TreePop();
		}

		ImGui::NewLine();
#endif

		if (ImGui::Button("Update##Objects"))
		{
			Features::ObjectsList::Update();
			Features::ObjectsList::Filter();
			GUI::PlayActionSound(true);
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		if (ImGui::InputText("Search Filter##Objects", Features::ObjectsList::filterBuffer, Features::ObjectsList::filterBufferSize))
		{
			Features::ObjectsList::Filter();
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		if (ImGui::Checkbox("Case Sensitive##Objects", &Features::ObjectsList::filterCaseSensitive))
		{
			Features::ObjectsList::Filter();
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		if (ImGui::ObjectFilterModeComboBox("##Objects", &Features::ObjectsList::filterMode))
		{
			Features::ObjectsList::Filter();
		}

		ImGui::NewLine();

		ImGui::PaginatedList("ObjectsList", &Features::ObjectsList::currentPage, Features::ObjectsList::filteredObjects, Features::ObjectsList::rowsPerPage, [](Unreal::Object::DataStructure& object)
		{
			bool isValid = Unreal::Object::IsValid(object.reference);

			ImGui::PushStyleColor(ImGuiCol_Text, isValid ? ImGui::Color::Green : ImGui::Color::Red);
			bool isTreeNodeOpen = ImGui::TreeNode(object.objectName.c_str());
			ImGui::PopStyleColor();

			if (isTreeNodeOpen)
			{
				ImGui::PushID(object.objectName.c_str());

				ImGui::BeginDisabled(std::strcmp(Features::ObjectsList::filterBuffer, object.objectName.c_str()) == 0);
				if (ImGui::Button("Focus On"))
				{
					std::snprintf(Features::ObjectsList::filterBuffer, sizeof(Features::ObjectsList::filterBuffer), object.objectName.c_str());
					Features::ObjectsList::filterMode = ImGui::E_ObjectFilterMode::ObjectName;

					GUI::PlayActionSound(true);
				}
				ImGui::EndDisabled();
				ImGui::SameLine();
				if (ImGui::Button("Refresh"))
				{
					Features::ObjectsList::Update(object);
					GUI::PlayActionSound(true);
				}

				ImGui::NewLine();

				ImGui::TextCopyable("Class: %s", object.className.c_str());
				if (ImGui::TreeNode("Class Hierarchy"))
				{
					Templates::ClassHierarchy::Draw(object.superClassesNames);
					ImGui::TreePop();
				}
				ImGui::TextCopyable("Object: %s", object.objectName.c_str());

				if (isValid)
				{
					ImGui::NewLine();

					Templates::Functions::Draw(object.reference);
				}

				ImGui::NewLine();
				ImGui::PopID();
				ImGui::TreePop();
			}
		});
	}
}

void Templates::Menus::Debug::Sub_Objects_ThreadSafe()
{
	__try
	{
		Templates::Menus::Debug::Sub_Objects();
	}
	__except (EXCEPTION())
	{
		ImGui::PopID();

		ImGui::TitleText("Something Isn't Right!");
		ImGui::Text("Consider updating the Objects list.");
	}
}

void Templates::Menus::Debug::Draw()
{
	if (ImGui::BeginMenu("Debug"))
	{
		if (Features::Debug::enabled == false)
		{
			if (ImGui::Button("Start"))
			{
				if (Features::Debug::autoUpdate == false)
					Features::Debug::Update_ThreadSafe();

				Features::Debug::enabled = true;
				GUI::PlayActionSound(true);
			}
		}
		else
		{
			if (Features::Debug::autoUpdate)
			{
				float updatesPerSecond = 1.0f / Features::Debug::autoUpdateDelay;
				if (updatesPerSecond > 1.0f)
					ImGui::Text("Updates %d Times per Second", (int32_t)(updatesPerSecond));
				else
				{
					float updatesPerMinute = 60.0f / Features::Debug::autoUpdateDelay;
					if (updatesPerMinute > 1.0f)
						ImGui::Text("Updates %d Times per Minute", (int32_t)(updatesPerMinute));
					else
					{
						float updatesPerHour = 3600.0f / Features::Debug::autoUpdateDelay;
						if (updatesPerHour > 1.0f)
							ImGui::Text("Updates %d Times per Hour", (int32_t)(updatesPerHour));
						else
						{
							float updatesPerDay = 86400.0f / Features::Debug::autoUpdateDelay;
							if (updatesPerDay > 1.0f)
								ImGui::Text("Updates %d Times per Day", (int32_t)(updatesPerDay));
							else
								ImGui::Text("Updates Periodically", (int32_t)(updatesPerDay));
						}
					}
				}
				if (ImGui::InputFloat("Auto Update Delay", &Features::Debug::autoUpdateDelay, 0.01f, 0.1f, "%.2f"))
				{
					if (Features::Debug::autoUpdateDelay < 0.01f)
						Features::Debug::autoUpdateDelay = 0.01f;

					Features::Config::Save();
				}

				const double now = ImGui::GetTime();
				const double elapsed = now - Features::Debug::lastUpdateTime;

				if (elapsed >= Features::Debug::autoUpdateDelay)
					Features::Debug::Update_ThreadSafe();
			}
			else
			{
				const double now = ImGui::GetTime();
				const double elapsed = now - Features::Debug::lastUpdateTime;
				if (elapsed < 60.0)
				{
					int seconds = (int)elapsed;
					ImGui::Text("Last Update: %d %s ago", seconds, (seconds == 1 ? "second" : "seconds"));
				}
				else if (elapsed < 3600.0)
				{
					int minutes = (int)(elapsed / 60.0);
					ImGui::Text("Last Update: %d %s ago", minutes, (minutes == 1 ? "minute" : "minutes"));
				}
				else if (elapsed < 86400.0)
				{
					int hours = (int)(elapsed / 3600.0);
					ImGui::Text("Last Update: %d %s ago", hours, (hours == 1 ? "hour" : "hours"));
				}
				else
				{
					int days = (int)(elapsed / 86400.0);
					ImGui::Text("Last Update: %d %s ago", days, (days == 1 ? "day" : "days"));
				}
			}


			ImGui::BeginDisabled(Features::Debug::autoUpdate);
			if (ImGui::Button("Update##DebugInformation"))
			{
				Features::Debug::Update_ThreadSafe();
				GUI::PlayActionSound(true);
			}
			ImGui::EndDisabled();
			ImGui::SameLine();
			if (ImGui::Checkbox("Auto", &Features::Debug::autoUpdate))
			{
				Features::Config::Save();
			}
			if (ImGui::Button("Stop"))
			{
				Features::Debug::enabled = false;
				GUI::PlayActionSound(true);
			}

			ImGui::CategorySeparator();

			Templates::Menus::Debug::Sub_Engine();

			ImGui::CategorySeparator();

			Templates::Menus::Debug::Sub_GameInstance();

			ImGui::CategorySeparator();

			Templates::Menus::Debug::Sub_GameMode();

			ImGui::CategorySeparator();

			Templates::Menus::Debug::Sub_PlayerController();

			ImGui::CategorySeparator();

			Templates::Menus::Debug::Sub_World();

			ImGui::CategorySeparator();

			Templates::Menus::Debug::Sub_Actors_ThreadSafe();
			
			ImGui::CategorySeparator();

			Templates::Menus::Debug::Sub_Widgets_ThreadSafe();

			ImGui::CategorySeparator();

			Templates::Menus::Debug::Sub_Objects_ThreadSafe();
			
			ImGui::CategorySeparator();

			if (Features::Debug::wasProjectNameObtained)
				ImGui::TextCopyable("Project Name: %s", Features::Debug::projectName.c_str());

			if (Features::Debug::wasProjectPlatformObtained)
				ImGui::TextCopyable("Project Platform: %s", Features::Debug::projectPlatform.c_str());

			ImGui::NewLine();

			if (Features::Debug::wasEngineVersionObtained)
				ImGui::TextCopyable("Engine Version: %s", Features::Debug::engineVersion.c_str());

			ImGui::NewLine();

			if (Features::Debug::wasUsernameObtained)
				ImGui::TextCopyable("Username: %s", Features::Debug::username.c_str());

			ImGui::NewLine();

			if (Features::Debug::wasCommandLineObtained)
			{
				ImGui::ReadOnlyInputText("Command Line:", Features::Debug::commandLine.c_str());
			}

			ImGui::MenuSpacer();
		}

		ImGui::EndMenu();
	}
}




void Templates::Menus::World::Draw()
{
	SDK::UWorld* world = SDK::UWorld::GetWorld();
	SDK::ULevel* persistentLevel = world ? world->PersistentLevel : nullptr;
	SDK::AWorldSettings* worldSettings = persistentLevel ? persistentLevel->WorldSettings : nullptr;

	bool worldObtained = world && persistentLevel && worldSettings;
	ImGui::BeginDisabled(worldObtained == false);
	if (ImGui::BeginMenu("World"))
	{
		if (worldObtained)
		{
			ImGui::TitleText("Level Streaming");
			if (ImGui::TreeNode("Details##LevelStreaming"))
			{
				if (ImGui::Button("Update##LevelStreaming"))
				{
					Features::LevelStreaming::Update();
					Features::LevelStreaming::Filter();
					GUI::PlayActionSound(true);
				}
				ImGui::SameLine();
				ImGui::Spacing();
				ImGui::SameLine();
				if (ImGui::InputText("Search Filter", Features::LevelStreaming::filterBuffer, Features::LevelStreaming::filterBufferSize))
				{
					Features::LevelStreaming::Filter();
				}
				ImGui::SameLine();
				ImGui::Spacing();
				ImGui::SameLine();
				if (ImGui::Checkbox("Case Sensitive", &Features::LevelStreaming::filterCaseSensitive))
				{
					Features::LevelStreaming::Filter();
				}
				ImGui::SameLine();
				ImGui::Spacing();
				ImGui::SameLine();
				if (ImGui::Checkbox("Editor Colors", &Features::LevelStreaming::useEditorColors))
				{
					Features::LevelStreaming::Filter();
				}

				ImGui::PaginatedList("LevelStreaming", &Features::LevelStreaming::currentPage, Features::LevelStreaming::filteredLevels, Features::LevelStreaming::rowsPerPage, [](Unreal::LevelStreaming::DataStructure& levelStreaming)
				{
					bool isValid = Unreal::Object::IsValid(levelStreaming.reference);

					bool shouldBeLoaded, shouldBeVisible = false;
					if (isValid)
					{
						shouldBeLoaded = levelStreaming.reference->bShouldBeLoaded;
						shouldBeVisible = levelStreaming.reference->bShouldBeVisible;
					}

					ImVec4 levelColor;
					if (Features::LevelStreaming::useEditorColors)
					{
						levelColor = { levelStreaming.levelColor.R, levelStreaming.levelColor.G, levelStreaming.levelColor.B, levelStreaming.levelColor.A };
					}
					else
					{
						if (isValid && shouldBeLoaded)
							levelColor = shouldBeVisible ? ImGui::LinearColor::Green : ImGui::LinearColor::Blue;
						else
							levelColor = ImGui::LinearColor::Red;
					}

					ImGui::PushStyleColor(ImGuiCol_Text, levelColor);
					bool isTreeNodeOpen = ImGui::TreeNode(levelStreaming.levelPath.c_str());
					ImGui::PopStyleColor();

					if (isTreeNodeOpen)
					{
						ImGui::PushID(levelStreaming.objectName.c_str());
						
						ImGui::TextBoolColored("Should Be Loaded:", shouldBeLoaded);
						if (isValid)
						{
							if (ImGui::Button("Enable##ShouldBeLoaded"))
							{
								if (levelStreaming.reference != nullptr)
								{
									levelStreaming.reference->SetShouldBeLoaded(true);
									GUI::PlayActionSound(true);
								}
								else
									GUI::PlayActionSound(false);
							}
							ImGui::SameLine();
							if (ImGui::Button("Disable##ShouldBeLoaded"))
							{
								if (levelStreaming.reference != nullptr)
								{
									levelStreaming.reference->SetShouldBeLoaded(false);
									GUI::PlayActionSound(true);
								}
								else
									GUI::PlayActionSound(false);
							}
						}

						ImGui::NewLine();

						ImGui::TextBoolColored("Should Be Visible:", shouldBeVisible);
						if (isValid)
						{
							if (ImGui::Button("Enable##ShouldBeVisible"))
							{
								if (levelStreaming.reference != nullptr)
								{
									levelStreaming.reference->SetShouldBeVisible(true);
									GUI::PlayActionSound(true);
								}
								else
									GUI::PlayActionSound(false);
							}
							ImGui::SameLine();
							if (ImGui::Button("Disable##ShouldBeVisible"))
							{
								if (levelStreaming.reference != nullptr)
								{
									levelStreaming.reference->SetShouldBeVisible(false);
									GUI::PlayActionSound(true);
								}
								else
									GUI::PlayActionSound(false);
							}
						}

						ImGui::NewLine();

						if (isValid)
						{
							bool worldSettingsPresent = levelStreaming.level.worldSettings.reference;
							ImGui::TextBoolPresence("World Settings:", worldSettingsPresent);
							if (worldSettingsPresent)
							{
								if (ImGui::TreeNode("World Settings"))
								{
									ImGui::TextCopyable("World Settings Class: %s", levelStreaming.level.worldSettings.className.c_str());
									ImGui::TextCopyable("World Settings Object: %s", levelStreaming.level.worldSettings.objectName.c_str());

									ImGui::NewLine();

									ImGui::TextBoolColored("High Priority Loading:", levelStreaming.level.worldSettings.highPriorityLoading);
									ImGui::TextBoolColored("Local High Priority Loading:", levelStreaming.level.worldSettings.localHighPriorityLoading);

									ImGui::NewLine();

									ImGui::Text("Units: 1m = %.2f", levelStreaming.level.worldSettings.unitsToMeters);

									ImGui::TreePop();
								}
							}
						}

						ImGui::NewLine();

						ImGui::PopID();
						ImGui::TreePop();
					}
				});

				ImGui::TreePop();
			}

			ImGui::NewLine();

#ifdef SOFT_PATH
			ImGui::TitleText("Level Instance");
			Templates::Descriptions::SoftPath::Draw("Level", "/Game/OpenWorld/Tile_X2Y8");

			if (ImGui::TreeNode("Details##LoadLevelInstance"))
			{
				ImGui::Text("Soft Path");
				ImGui::InputText("##LoadLevelInstance##Path", Features::LoadLevelInstance::levelPathBuffer, Features::LoadLevelInstance::levelPathBufferSize);

				ImGui::NewLine();

				ImGui::Text("Level Location:");
				ImGui::SameLine();
				ImGui::InputFloat3("##LevelLocationOffset", Features::LoadLevelInstance::locationOffset);

				ImGui::Text("Level Rotation:");
				ImGui::SameLine();
				ImGui::InputFloat3("##LevelRotationOffset", Features::LoadLevelInstance::rotationOffset);

				ImGui::NewLine();

				if (ImGui::Button("Load##LoadLevelInstance"))
				{
					std::vector<std::wstring> levelPathCollection = Utilities::String::Split(Features::LoadLevelInstance::levelPathBuffer, L'|');
					if (levelPathCollection.size() > 0)
					{
						bool anyLevelLoaded = false;
						SDK::FVector locationOffset = SDK::FVector(Features::LoadLevelInstance::locationOffset[0], Features::LoadLevelInstance::locationOffset[1], Features::LoadLevelInstance::locationOffset[2]);
						SDK::FRotator rotationOffset = SDK::FRotator(Features::LoadLevelInstance::rotationOffset[0], Features::LoadLevelInstance::rotationOffset[1], Features::LoadLevelInstance::rotationOffset[2]);

						for (std::wstring levelPath : levelPathCollection)
						{
							std::wstring normalizedPath = Unreal::Object::NormalizeObjectPath(levelPath);
							if (Unreal::LevelStreaming::LoadLevelInstance(normalizedPath, locationOffset, rotationOffset, true))
								anyLevelLoaded = true;
						}

						GUI::PlayActionSound(anyLevelLoaded);
					}
					else
						GUI::PlayActionSound(false);
				}

				ImGui::TreePop();
			}

			ImGui::NewLine();
			ImGui::TitleText("Level Sequence");
			ImGui::SmallText("Dynamic level sequence playing by soft path, for example \"/Game/OpenWorld/Sequences/LS_TowerExplosion.LS_TowerExplosion\".");
			ImGui::SmallText("Feature supports combined input using the '|' separator between paths.");

			if (ImGui::TreeNode("Details##PlayLevelSequence"))
			{
				ImGui::Text("Soft Path");
				ImGui::InputText("##PlayLevelSequence##Path", Features::PlayLevelSequence::levelSequencePathBuffer, Features::PlayLevelSequence::levelSequencePathBufferSize);

				ImGui::NewLine();

				ImGui::Text("Start Time");
				ImGui::SliderFloatEditable("##PlayLevelSequence##StartTime", &Features::PlayLevelSequence::startTime, 0.0f, 60.0f);

				ImGui::NewLine();

				ImGui::Text("Play Rate");
				ImGui::SliderFloatEditable("##PlayLevelSequence##PlayRate", &Features::PlayLevelSequence::playRate, 0.1f, 10.0f);

				ImGui::NewLine();

				ImGui::Text("Loop Count");
				ImGui::SliderIntEditable("##PlayLevelSequence##LoopCount", &Features::PlayLevelSequence::loopCount, 1, 100);

				ImGui::NewLine();

				if (ImGui::Button("Create##PlayLevelSequence"))
				{
					std::vector<std::wstring> levelSequencePathCollection = Utilities::String::Split(Features::PlayLevelSequence::levelSequencePathBuffer, L'|');
					if (levelSequencePathCollection.size() > 0)
					{
						bool anySequenceCreated = false;

						for (std::wstring levelSequencePath : levelSequencePathCollection)
						{
							std::wstring normalizedPath = Unreal::Object::NormalizeObjectPath(levelSequencePath);
							if (Unreal::Level::CreateLevelSequence_ThreadSafe(normalizedPath, Features::PlayLevelSequence::startTime, Features::PlayLevelSequence::playRate, Features::PlayLevelSequence::loopCount))
								anySequenceCreated = true;
						}

						GUI::PlayActionSound(anySequenceCreated);
					}
					else
						GUI::PlayActionSound(false);
				}

				ImGui::TreePop();
			}

			ImGui::NewLine();
#endif

			ImGui::TitleText("Gravity");
			if (ImGui::TreeNode("Details##WorldGravity"))
			{
				ImGui::Text("Global Gravity");
				ImGui::SliderFloatEditable("##WorldGravity##Global", &worldSettings->GlobalGravityZ, -980.0f, 980.0f);
				ImGui::SameLine();
				bool isGlobalGravitySet = worldSettings->bGlobalGravitySet == 1;
				if (ImGui::Checkbox("Is Set##WorldGravity##Global", &isGlobalGravitySet))
				{
					worldSettings->bGlobalGravitySet = static_cast<uint8_t>(isGlobalGravitySet);
				}

				ImGui::NewLine();

				ImGui::Text("World Gravity");
				ImGui::SliderFloatEditable("##WorldGravity##World", &worldSettings->WorldGravityZ, -980.0f, 980.0f);
				ImGui::SameLine();
				bool isWorldGravitySet = worldSettings->bWorldGravitySet == 1;
				if (ImGui::Checkbox("Is Set##WorldGravity##World", &isWorldGravitySet))
				{
					worldSettings->bWorldGravitySet = static_cast<uint8_t>(isWorldGravitySet);
				}

				ImGui::TreePop();
			}

			ImGui::CategorySeparator();

			ImGui::TitleText("Time");
			if (ImGui::TreeNode("Details##WorldTime"))
			{
				bool isTimePaused = SDK::UGameplayStatics::IsGamePaused(world);
				ImGui::TextBoolColored("Is Paused:", isTimePaused);
				ImGui::BeginDisabled(isTimePaused);
				if (ImGui::Button("Pause"))
				{
					bool wasSuccessfull = SDK::UGameplayStatics::SetGamePaused(world, true);
					GUI::PlayActionSound(wasSuccessfull);
				}
				ImGui::EndDisabled();
				ImGui::SameLine();
				ImGui::BeginDisabled(isTimePaused == false);
				if (ImGui::Button("Unpause"))
				{
					bool wasSuccessfull = SDK::UGameplayStatics::SetGamePaused(world, false);
					GUI::PlayActionSound(wasSuccessfull);
				}
				ImGui::EndDisabled();

				ImGui::NewLine();

				ImGui::Text("Time Dilation");
				double timeDilation = worldSettings->TimeDilation;
				double minTimeDilation = worldSettings->MinGlobalTimeDilation;
				double maxTimeDilation = worldSettings->MaxGlobalTimeDilation;

				if (ImGui::SliderDoubleEditable("##TimeDilation", &timeDilation, minTimeDilation, maxTimeDilation))
				{
					worldSettings->TimeDilation = timeDilation;
				}
				if (ImGui::TreeNode("Settings##TimeDilation"))
				{
					ImGui::Text("Minimum");
					if (ImGui::SliderDoubleEditable("##TimeDilation##Min", &minTimeDilation, 0.0f, 20.0f))
					{
						worldSettings->MinGlobalTimeDilation = minTimeDilation;
					}

					ImGui::NewLine();

					ImGui::Text("Maximum");
					if (ImGui::SliderDoubleEditable("##TimeDilation##Max", &maxTimeDilation, 0.0f, 20.0f))
					{
						worldSettings->MaxGlobalTimeDilation = maxTimeDilation;
					}

					ImGui::TreePop();
				}

				ImGui::NewLine();

				ImGui::Text("Demo Time Dilation");
				double demoTimeDilation = worldSettings->DemoPlayTimeDilation;

				if (ImGui::SliderDoubleEditable("##DemoTimeDilation", &demoTimeDilation, 0.0f, 20.0f))
				{
					worldSettings->DemoPlayTimeDilation = demoTimeDilation;
				}

				ImGui::TreePop();
			}

			ImGui::CategorySeparator();

			bool enableAISystem = worldSettings->bEnableAISystem == 1;
			if (ImGui::Checkbox("Enable AI System", &enableAISystem))
			{
				worldSettings->bEnableAISystem = static_cast<uint8_t>(enableAISystem);
			}

			bool enableNavigationSystem = worldSettings->bEnableNavigationSystem == 1;
			if (ImGui::Checkbox("Enable Navigation System", &enableNavigationSystem))
			{
				worldSettings->bEnableNavigationSystem = static_cast<uint8_t>(enableNavigationSystem);
			}

			ImGui::NewLine();

			ImGui::InputFloat("Kill Volume Z", &worldSettings->KillZ, 10.0f, 100.0f);
		}
		else
		{
			if (world == nullptr)
				ImGui::Text("World Doesn't Exist!");
			else if (persistentLevel == nullptr)
				ImGui::Text("Persistent Level Doesn't Exist!");
			else if (worldSettings == nullptr)
				ImGui::Text("World Settings Doesn't Exist!");
			else
				ImGui::Text("Something Went Wrong.");
		}

		ImGui::MenuSpacer();

		ImGui::EndMenu();
	}
	ImGui::EndDisabled();
}

void Templates::Menus::World::Draw_ThreadSafe()
{
	__try
	{
		Templates::Menus::World::Draw();
	}
	__except (EXCEPTION())
	{
		ImGui::PopID();

		ImGui::TitleText("Something Isn't Right!");
		ImGui::Text("Fatal Error / Crash has been prevented.");
	}
}




void Templates::Menus::Character::Draw()
{
	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	SDK::ACharacter* character = playerController ? playerController->Character : nullptr;
	SDK::UCharacterMovementComponent* movementComponent = (character && character->CharacterMovement) ? character->CharacterMovement : nullptr;

	bool characterObtained = playerController && character && movementComponent;
	ImGui::BeginDisabled(characterObtained == false);
	if (ImGui::BeginMenu("Character"))
	{
		if (characterObtained)
		{
			ImGui::TextCopyable("Character: %s", character->GetFullName().c_str());

			ImGui::NewLine();

			Unreal::Transform characterTransform = Unreal::Actor::GetTransform(character);
			ImGui::TextVectorColored("Location: ", characterTransform.location);
			ImGui::TextRotatorColored("Rotation: ", characterTransform.rotation);
			ImGui::TextVectorColored("Scale:    ", characterTransform.scale);
			Templates::LocationRotationScale::Draw(character);
			
			ImGui::NewLine();

			ImGui::TitleText("Positions");
			if (ImGui::TreeNode("Details##Positions"))
			{
				if (ImGui::Button("Reload"))
				{
					Features::Positions::Load();
					GUI::GUI::PlayActionSound(true);
				}

				static int selectedPositionIndex = -1;

				if (ImGui::BeginTable("PositionsLayout", 2, ImGuiTableFlags_SizingFixedFit))
				{
					ImGui::TableSetupColumn("PositionsLeftSide", ImGuiTableColumnFlags_WidthFixed, 400.0f);
					ImGui::TableSetupColumn("PositionsRightSide", ImGuiTableColumnFlags_WidthFixed);

					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);

					/* LEFT SIDE - Table. */
					ImGui::Text("Stored Positions:");
					if (ImGui::BeginChild("PositionsList", ImVec2(0, 600), true, ImGuiWindowFlags_HorizontalScrollbar))
					{
						/* 2 columns: ID, Title */
						if (ImGui::BeginTable("PositionsTable", 2, ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingFixedFit))
						{
							ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 40.0f);
							ImGui::TableSetupColumn("Title", ImGuiTableColumnFlags_WidthStretch);
							ImGui::TableHeadersRow();

							for (size_t i = 0; i < Features::Positions::entries.size(); i++)
							{
								ImGui::TableNextRow();

								// ID + Selectable
								ImGui::TableSetColumnIndex(0);

								char positionIdLabel[Features::Positions::newEntryTitleBufferSize];
								sprintf_s(positionIdLabel, "%d", (int)i);

								/* Make line highlighted by clicking on ID. */
								if (ImGui::Selectable(positionIdLabel, selectedPositionIndex == i, ImGuiSelectableFlags_SpanAllColumns))
								{
									selectedPositionIndex = (int)i;
								}

								/* Title */
								ImGui::TableSetColumnIndex(1);
								ImGui::TextUnformatted(Features::Positions::entries[i].title.c_str());
							}

							ImGui::EndTable();
						}
					}
					ImGui::EndChild();

					ImGui::TableSetColumnIndex(1);

					/* RIGHT SIDE - Buttons. */
					ImGui::Text("Actions:");

					bool isPositionsListFull = Features::Positions::entries.size() >= Features::Positions::entriesLimit;
					ImGui::BeginDisabled(isPositionsListFull);
					ImGui::InputTextWithHint("##PositionTitle", "Position Title", Features::Positions::newEntryTitleBuffer, Features::Positions::newEntryTitleBufferSize);

					if (ImGui::Button("Store Current Position"))
					{
						if (isPositionsListFull == false)
						{
							Features::Positions::PositionEntry newPositionEntry;
							newPositionEntry.title = Utilities::String::ToString(Features::Positions::newEntryTitleBuffer);
							newPositionEntry.location = characterTransform.location;
							newPositionEntry.rotation = characterTransform.rotation;
							Features::Positions::entries.push_back(newPositionEntry);

							Features::Positions::Save();
							GUI::PlayActionSound(true);
						}
						else
							GUI::PlayActionSound(false);
					}
					ImGui::EndDisabled();

					ImGui::NewLine();

					bool isPositionEntrySelected = (selectedPositionIndex >= 0) && (selectedPositionIndex < Features::Positions::entries.size());
					if (isPositionEntrySelected)
					{
						ImGui::TextVectorColored("Location:", Features::Positions::entries[selectedPositionIndex].location);
						ImGui::TextRotatorColored("Rotation:", Features::Positions::entries[selectedPositionIndex].rotation);
						if (ImGui::Button("Teleport To Selected"))
						{
							if (selectedPositionIndex >= 0 && selectedPositionIndex < Features::Positions::entries.size())
							{
								bool isSuccess = Unreal::Actor::TeleportTo(character, Features::Positions::entries[selectedPositionIndex].location, Features::Positions::entries[selectedPositionIndex].rotation);
								GUI::PlayActionSound(isSuccess);
							}
							else
								GUI::PlayActionSound(false);
						}
						ImGui::SameLine();
						if (ImGui::Button("Remove Selected"))
						{
							if (selectedPositionIndex >= 0 && selectedPositionIndex < Features::Positions::entries.size())
							{
								Features::Positions::entries.erase(Features::Positions::entries.begin() + selectedPositionIndex);
								selectedPositionIndex = -1;

								Features::Positions::Save();
								GUI::PlayActionSound(true);
							}
							else
								GUI::PlayActionSound(false);
						}
					}

					ImGui::EndTable();
				}

				ImGui::TreePop();
			}

			ImGui::NewLine();

			ImGui::TitleText("Movement");
			if (ImGui::TreeNode("Details##CharacterMovement"))
			{
				bool isCheatFlying = movementComponent->bCheatFlying;
				bool isGhost = isCheatFlying && (character->bActorEnableCollision == false);

				if (isCheatFlying)
				{
					ImGui::Text("Character Is In %s Mode", isGhost ? "Ghost" : "Fly");
				}
				else
				{
					SDK::EMovementMode characterMovementMode = movementComponent->MovementMode;
					std::string movementMode;
					switch (characterMovementMode)
					{
						case SDK::EMovementMode::MOVE_Walking:
							movementMode = "Walking";
							break;

						case SDK::EMovementMode::MOVE_NavWalking:
							movementMode = "Navigation Walking";
							break;

						case SDK::EMovementMode::MOVE_Falling:
							movementMode = "Falling";
							break;

						case SDK::EMovementMode::MOVE_Swimming:
							movementMode = "Swimming";
							break;

						case SDK::EMovementMode::MOVE_Flying:
							movementMode = "Flying";
							break;

						default:
							movementMode = std::to_string(static_cast<uint8_t>(characterMovementMode));
							break;
					}

					ImGui::Text("Character Is %s", movementMode);
				}
				
				ImGui::Text("Custom Movement Mode: %d", movementComponent->CustomMovementMode);

				ImGui::NewLine();

				/* 0 corresponds for default vertical size. */
				static const ImVec2 buttonSize = { 128.0f, 0.0f };

				ImGui::BeginDisabled(isCheatFlying && isGhost);
				if (ImGui::Button("Ghost", buttonSize))
				{
					Features::CharacterMovement::Ghost();
				}
				ImGui::EndDisabled();
				ImGui::SameLine();
				ImGui::BeginDisabled(isCheatFlying && isGhost == false);
				if (ImGui::Button("Fly", buttonSize))
				{
					Features::CharacterMovement::Fly();
				}
				ImGui::EndDisabled();
				ImGui::SameLine();
				ImGui::BeginDisabled(isCheatFlying == false);
				if (ImGui::Button("Walk", buttonSize))
				{
					Features::CharacterMovement::Walk();
				}
				ImGui::EndDisabled();

				ImGui::NewLine();

				ImGui::KeyBindingInput("Ghost Key Binding:##Ghost", &Inputs::Keybindings::characterMovement_Ghost);
				ImGui::KeyBindingInput("Fly Key Binding:  ##Fly", &Inputs::Keybindings::characterMovement_Fly);
				ImGui::KeyBindingInput("Walk Key Binding: ##Walk", &Inputs::Keybindings::characterMovement_Walk);

				ImGui::NewLine();

				ImGui::TitleText("Directional Movement");
				ImGui::SmallText("When the character is Flying or in Ghost mode, moving forward teleports them in the direction");
				ImGui::SmallText("the camera is facing, allowing for quick and easy navigation through the world.");
				if (ImGui::TreeNode("Settings##DirectionalMovement"))
				{
					if (ImGui::Checkbox("Enabled##DirectionalMovement", &Features::DirectionalMovement::enabled))
					{
						Features::Config::Save();
					}
					ImGui::NewLine();
					if (ImGui::Checkbox("Omni-Movement##DirectionalMovement", &Features::DirectionalMovement::omniMovement))
					{
						Features::Config::Save();
					}
					ImGui::SameLine();
					ImGui::QuestionMarkHint("Allows movement in all directions (Backward, Left, Right, Up & Down).");
					ImGui::BeginDisabled(Features::DirectionalMovement::omniMovement == false);
					ImGui::KeyBindingInput("Move Up  ", &Inputs::Keybindings::characterOmniMovement_Up);
					ImGui::KeyBindingInput("Move Down", &Inputs::Keybindings::characterOmniMovement_Down);

					ImGui::NewLine();

					if (ImGui::Checkbox("Independent Omni-Movement##DirectionalMovement", &Features::DirectionalMovement::independentOmniMovement))
					{
						Features::Config::Save();
					}
					ImGui::SameLine();
					ImGui::QuestionMarkHint("Move character ignoring current velocity.");
					ImGui::EndDisabled();
					ImGui::BeginDisabled(Features::DirectionalMovement::independentOmniMovement == false);
					ImGui::KeyBindingInput("Move Forward ", &Inputs::Keybindings::characterOmniMovement_Forward);
					ImGui::KeyBindingInput("Move Backward", &Inputs::Keybindings::characterOmniMovement_Backward);
					ImGui::KeyBindingInput("Move Left    ", &Inputs::Keybindings::characterOmniMovement_Left);
					ImGui::KeyBindingInput("Move Right   ", &Inputs::Keybindings::characterOmniMovement_Right);
					ImGui::EndDisabled();

					ImGui::NewLine();

					ImGui::Text("Movement Step");
					ImGui::SliderFloatEditable("##DirectionalMovement##MovementStep", &Features::DirectionalMovement::step, 1.0f, 100.0f);
					if (ImGui::IsItemDeactivatedAfterEdit())
					{
						Features::Config::Save();
					}

					ImGui::NewLine();

					ImGui::Text("Movement Delay");
					ImGui::SliderFloatEditable("##DirectionalMovement##MovementDelay", &Features::DirectionalMovement::delay, 0.050f, 1.0f);
					if (ImGui::IsItemDeactivatedAfterEdit())
					{
						Features::Config::Save();
					}

					ImGui::TreePop();
				}

				ImGui::CategorySeparator();

				ImGui::Text("Gravity Scale");
				ImGui::SliderFloatEditable("##GravityScale", &movementComponent->GravityScale, 0.0f, 10.0f);

				ImGui::NewLine();

				ImGui::Text("Maximum Walking Speed");
				ImGui::SliderFloatEditable("##MaximumWalkingSpeed", &movementComponent->MaxWalkSpeed, 0.0f, 1000.0f);

				ImGui::NewLine();

				ImGui::Text("Maximum Crouching Speed");
				ImGui::SliderFloatEditable("##MaximumCrouchingSpeed", &movementComponent->MaxWalkSpeedCrouched, 0.0f, 1000.0f);

				ImGui::NewLine();

				ImGui::Text("Maximum Swimming Speed");
				ImGui::SliderFloatEditable("##MaximumSwimmingSpeed", &movementComponent->MaxSwimSpeed, 0.0f, 1000.0f);

				ImGui::NewLine();

				ImGui::Text("Maximum Flying Speed");
				ImGui::SliderFloatEditable("##MaximumFlyingSpeed", &movementComponent->MaxFlySpeed, 0.0f, 1000.0f);

				ImGui::NewLine();

				ImGui::Text("Maximum Custom Movement Speed");
				ImGui::SliderFloatEditable("##MaximumCustomMovementSpeed", &movementComponent->MaxCustomMovementSpeed, 0.0f, 1000.0f);

				ImGui::NewLine();

				ImGui::Text("Maximum Acceleration");
				ImGui::SliderFloatEditable("##MaximumAcceleration", &movementComponent->MaxAcceleration, 0.0f, 10000.0f);

				ImGui::NewLine();

				ImGui::Text("Maximum Step Height");
				ImGui::SliderFloatEditable("##MaximumStepHeight", &movementComponent->MaxStepHeight, 0.0f, 100.0f);

				ImGui::NewLine();

				ImGui::Text("Weight");
				ImGui::SliderFloatEditable("##Weight", &movementComponent->Mass, 0.0f, 1000.0f);

				ImGui::NewLine();

				ImGui::TextFloatColored("Walkable Floor Z:", movementComponent->WalkableFloorZ);

				ImGui::TreePop();
			}

			ImGui::NewLine();

			ImGui::TitleText("Input");
			if (ImGui::TreeNode("Details##Input"))
			{
				if (ImGui::Button("Enable Input"))
				{
					if (character)
					{
						character->EnableInput(playerController);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::SameLine();
				if (ImGui::Button("Disable Input"))
				{
					if (character)
					{
						character->DisableInput(playerController);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}

				ImGui::NewLine();

				bool isMoveInputIgnored = playerController->IsMoveInputIgnored();
				ImGui::TextBoolColored("Ignore Move Input:", isMoveInputIgnored);
				ImGui::BeginDisabled(isMoveInputIgnored);
				if (ImGui::Button("Enable##IgnoreMoveInput"))
				{
					if (playerController)
					{
						playerController->SetIgnoreMoveInput(true);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::EndDisabled();
				ImGui::SameLine();
				ImGui::BeginDisabled(isMoveInputIgnored == false);
				if (ImGui::Button("Disable##IgnoreMoveInput"))
				{
					if (playerController)
					{
						playerController->SetIgnoreMoveInput(false);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::EndDisabled();

				ImGui::NewLine();

				bool isLookInputIgnored = playerController->IsLookInputIgnored();
				ImGui::TextBoolColored("Ignore Look Input:", isLookInputIgnored);
				ImGui::BeginDisabled(isLookInputIgnored);
				if (ImGui::Button("Enable##IgnoreLookInput"))
				{
					if (playerController)
					{
						playerController->SetIgnoreLookInput(true);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::EndDisabled();
				ImGui::SameLine();
				ImGui::BeginDisabled(isMoveInputIgnored == false);
				if (ImGui::Button("Disable##IgnoreLookInput"))
				{
					if (playerController)
					{
						playerController->SetIgnoreLookInput(false);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::EndDisabled();

				ImGui::NewLine();

				if (ImGui::Button("Focus Input On Game Only"))
				{
					if (playerController)
					{
#ifdef UE5
						SDK::UWidgetBlueprintLibrary::SetInputMode_GameOnly(playerController, true);
#else
						SDK::UWidgetBlueprintLibrary::SetInputMode_GameOnly(playerController);
#endif
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}

				ImGui::TreePop();
			}

			ImGui::CategorySeparator();

			if (ImGui::Button("Jump"))
			{
				Features::CharacterMovement::Jump();
			}
			ImGui::InputInt("Jump Limit", &character->JumpMaxCount, 1, 1);
			ImGui::InputFloat("Jump Height", &movementComponent->JumpZVelocity, 0.1f, 1.0f);
			ImGui::KeyBindingInput("Jump Key Binding:##Jump", &Inputs::Keybindings::characterMovement_Jump);

			ImGui::NewLine();

			if (ImGui::Button("Launch"))
			{
				Features::CharacterMovement::Launch();
			}
			ImGui::InputFloat3("Launch Velocity", Features::CharacterMovement::launchVelocity);
			ImGui::KeyBindingInput("Launch Key Binding:##Launch", &Inputs::Keybindings::characterMovement_Launch);

			ImGui::NewLine();

			if (ImGui::Button("Dash"))
			{
				Features::CharacterMovement::Dash();
			}
			ImGui::InputDouble("Dash Strength", &Features::CharacterMovement::dashStrength, 0.1f, 1.0f);
			ImGui::KeyBindingInput("Dash Key Binding:##Dash", &Inputs::Keybindings::characterMovement_Dash);

			ImGui::CategorySeparator();

			SDK::APlayerCameraManager* cameraManager = playerController->PlayerCameraManager;
			ImGui::TitleText("Camera");
			ImGui::BeginDisabled(cameraManager == nullptr);
			if (ImGui::TreeNode("Details##Camera"))
			{
				if (cameraManager)
				{
					/* 0 corresponds for default vertical size. */
					static const ImVec2 buttonSize = { 204.0f, 0.0f };

					if (ImGui::Button("Start Fade", buttonSize))
					{
						Features::Camera::StartFade();
					}
					ImGui::SameLine();
					if (ImGui::Button("Stop Fade", buttonSize))
					{
						Features::Camera::StopFade();
					}

					if (ImGui::InputFloat("Fade From Alpha", &Features::Camera::fadeFromAlpha, 0.01f, 0.1f))
					{
						if (Features::Camera::fadeFromAlpha < 0.0f)
							Features::Camera::fadeFromAlpha = 0.0f;

						if (Features::Camera::fadeFromAlpha > 1.0f)
							Features::Camera::fadeFromAlpha = 1.0f;
					}

					if (ImGui::InputFloat("Fade To Alpha", &Features::Camera::fadeToAlpha, 0.01f, 0.1f))
					{
						if (Features::Camera::fadeToAlpha < 0.0f)
							Features::Camera::fadeToAlpha = 0.0f;

						if (Features::Camera::fadeToAlpha > 1.0f)
							Features::Camera::fadeToAlpha = 1.0f;
					}

					ImGui::InputFloat("Fade Duration", &Features::Camera::fadeDuration, 0.1f, 1.0f);
					ImGui::ColorPicker4("Fade Color", Features::Camera::fadeColor);

					ImGui::NewLine();

					ImGui::Checkbox("Fade Audio", &Features::Camera::fadeAudio);
					ImGui::Checkbox("Fade Persistent", &Features::Camera::fadePersistent);

					ImGui::NewLine();

					ImGui::KeyBindingInput("Start Fade Key Binding:", &Inputs::Keybindings::characterCamera_StartFade);
					ImGui::KeyBindingInput("Stop Fade Key Binding:", &Inputs::Keybindings::characterCamera_StopFade);
				}
				else
					ImGui::Text("Camera Manager Doesn't Exist!");

				ImGui::TreePop();
			}
			ImGui::EndDisabled();

			ImGui::MenuSpacer();
		}
		else
		{
			if (playerController == nullptr)
				ImGui::Text("Player Controller Doesn't Exist!");
			else if (character == nullptr)
				ImGui::Text("Character Doesn't Exist!");
			else if (movementComponent == nullptr)
				ImGui::Text("Movement Component Doesn't Exist!");
			else
				ImGui::Text("Something Went Wrong.");
		}

		ImGui::EndMenu();
	}
	ImGui::EndDisabled();
}

void Templates::Menus::Character::Draw_ThreadSafe()
{
	__try
	{
		Templates::Menus::Character::Draw();
	}
	__except (EXCEPTION())
	{
		ImGui::PopID();

		ImGui::TitleText("Something Isn't Right!");
		ImGui::Text("Fatal Error / Crash has been prevented.");
	}
}




void Templates::Menus::FreeCamera::Draw()
{
	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	ImGui::BeginDisabled(playerController == nullptr);
	if (ImGui::BeginMenu("FCamera"))
	{
		if (playerController)
		{
			ImGui::PushID("##FreeCamera");

			if (ImGui::Button("Toggle"))
			{
				Features::FreeCamera::Toggle();
			}
			ImGui::KeyBindingInput("Key Binding:##Toggle", &Inputs::Keybindings::freeCamera_Toggle);

			ImGui::NewLine();

			if (ImGui::Checkbox("Force Freeze Player", &Features::FreeCamera::forceFreezePlayer))
			{
				Features::Config::Save();
			}

			if (ImGui::Checkbox("Force Disable Player Input", &Features::FreeCamera::forceDisablePlayerInput))
			{
				Features::Config::Save();
			}

			ImGui::NewLine();

			ImGui::Text("Movement Step");
			ImGui::SliderFloat("##MovementStep", &Features::FreeCamera::cameraMovementStep, 0.01f, 100.0f);
			if (ImGui::IsItemDeactivatedAfterEdit())
			{
				Features::Config::Save();
			}

			ImGui::KeyBindingInput("Move Up:      ", &Inputs::Keybindings::freeCamera_MoveUp);
			ImGui::KeyBindingInput("Move Down:    ", &Inputs::Keybindings::freeCamera_MoveDown);
			ImGui::KeyBindingInput("Move Forward: ", &Inputs::Keybindings::freeCamera_MoveForward);
			ImGui::KeyBindingInput("Move Backward:", &Inputs::Keybindings::freeCamera_MoveBackward);
			ImGui::KeyBindingInput("Move Left:    ", &Inputs::Keybindings::freeCamera_MoveLeft);
			ImGui::KeyBindingInput("Move Right:   ", &Inputs::Keybindings::freeCamera_MoveRight);

			ImGui::NewLine();

			ImGui::Text("Rotation Step");
			ImGui::SliderFloat("##RotationStep", &Features::FreeCamera::cameraRotationStep, 0.01f, 10.0f);
			if (ImGui::IsItemDeactivatedAfterEdit())
			{
				Features::Config::Save();
			}

			ImGui::KeyBindingInput("Rotate Up:    ", &Inputs::Keybindings::freeCamera_RotateUp);
			ImGui::KeyBindingInput("Rotate Down:  ", &Inputs::Keybindings::freeCamera_RotateDown);
			ImGui::KeyBindingInput("Rotate Left:  ", &Inputs::Keybindings::freeCamera_RotateLeft);
			ImGui::KeyBindingInput("Rotate Right: ", &Inputs::Keybindings::freeCamera_RotateRight);

			ImGui::NewLine();

			ImGui::TitleText("Mouse Control");
			if (ImGui::TreeNode("Details##MouseControl"))
			{
				if (ImGui::Checkbox("Enabled##MouseControl", &Features::FreeCamera::useMouseControl))
				{
					Features::Config::Save();
				}
				ImGui::NewLine();

				ImGui::Text("Sensitivity");
				ImGui::SliderFloatEditable("##MouseControl##Sensitivity", &Features::FreeCamera::mouseControlSensitivity, 0.001f, 1.0f);
				if (ImGui::IsItemDeactivatedAfterEdit())
				{
					Features::Config::Save();
				}

				ImGui::NewLine();

				ImGui::Text("Maximum Delta");
				ImGui::BeginDisabled(Features::FreeCamera::mouseControlLimitMaximumDelta == false);
				ImGui::SliderFloatEditable("##MouseControl##MaximumDelta", &Features::FreeCamera::mouseControlMaximumDelta, 1.0f, 100.0f);
				if (ImGui::IsItemDeactivatedAfterEdit())
				{
					Features::Config::Save();
				}
				ImGui::EndDisabled();
				ImGui::SameLine();
				if (ImGui::Checkbox("Limit", &Features::FreeCamera::mouseControlLimitMaximumDelta))
				{
					Features::Config::Save();
				}

				ImGui::NewLine();

				if (ImGui::Checkbox("Invert X Axis", &Features::FreeCamera::mouseControlXInverted))
				{
					Features::Config::Save();
				}
				if (ImGui::Checkbox("Invert Y Axis", &Features::FreeCamera::mouseControlYInverted))
				{
					Features::Config::Save();
				}

				ImGui::NewLine();

				if (ImGui::Checkbox("Control While Holding RMB", &Features::FreeCamera::mouseControlOnHold))
				{
					Features::Config::Save();
				}

				ImGui::TreePop();
			}

			ImGui::NewLine();

			if (ImGui::Button("Player -> FCamera"))
			{
				GUI::PlayActionSound(Features::FreeCamera::TeleportPlayerToCamera());
			}
			ImGui::KeyBindingInput("Key Binding:##TeleportPlayerToFCamera", &Inputs::Keybindings::freeCamera_TeleportPlayerToCamera);

			ImGui::NewLine();

			if (ImGui::Button("FCamera -> Player"))
			{
				GUI::PlayActionSound(Features::FreeCamera::TeleportCameraToPlayer());
			}
			ImGui::KeyBindingInput("Key Binding:####TeleportFCameraToPlayer", &Inputs::Keybindings::freeCamera_TeleportCameraToPlayer);

			ImGui::PopID();
			ImGui::MenuSpacer();
		}
		else
			ImGui::Text("Player Controller Doesn't Exist!");

		ImGui::EndMenu();
	}
	ImGui::EndDisabled();
}




void Templates::Menus::Settings::Draw()
{
	if (ImGui::BeginMenu("Settings"))
	{
		if (ImGui::Checkbox("Enable Sound", &Features::Menu::enableSound))
		{
			Features::Config::Save();
		}

		ImGui::NewLine();

		if (ImGui::Checkbox("Use Vector Font", &Features::Menu::useVectorFont))
		{
			ImGuiIO& io = ImGui::GetIO();
			io.FontDefault = Features::Menu::useVectorFont ? Features::Menu::fontVector : Features::Menu::fontBitmap;

			Features::Config::Save();
		}

		ImGui::EndMenu();
	}
}




void Templates::Menus::BootlegConsole::Draw()
{
	ImGui::Text("Console:");
	ImGui::SameLine();
	ImGui::PushItemWidth(320);
	ImGui::InputText("##BootlegConsole", Features::BootlegConsole::buffer, Features::BootlegConsole::bufferSize);
	ImGui::SameLine();
	if (ImGui::Button("Execute"))
	{
		std::wstring command = Utilities::String::ToWString(Features::BootlegConsole::buffer);
		if (command.size() > 0)
		{
			GUI::PlayActionSound(Unreal::Console::ExecuteConsoleCommand(command));
		}
		else
			GUI::PlayActionSound(false);
	}
	ImGui::PopItemWidth();
}