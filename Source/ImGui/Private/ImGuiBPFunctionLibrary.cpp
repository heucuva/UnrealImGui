// Distributed under the MIT License (MIT) (see accompanying LICENSE file)

#include "ImGuiBPFunctionLibrary.h"
#include "ImGuiModule.h"

#include <imgui.h>
#include "Misc/Optional.h"

// Context creation and access

// ==== Main ====

void UImGuiBPFunctionLibrary::SetShowingImgui(bool Showing)
{
	// HACK: assume for now that the gui is showing if input is enabled.
	FImGuiModule::Get().GetProperties().SetInputEnabled(Showing);
}

bool UImGuiBPFunctionLibrary::IsShowingImgui()
{
	// HACK: assume for now that the gui is showing if input is enabled.
	return FImGuiModule::Get().GetProperties().IsInputEnabled();
}

void UImGuiBPFunctionLibrary::ToggleShowingImgui()
{
	// HACK: assume for now that the gui is showing if input is enabled.
	FImGuiModule::Get().GetProperties().ToggleInput();
}

// ==== Demo, Debug, Information ====

void UImGuiBPFunctionLibrary::ShowDemoWindow(bool& bOpen)
{
	ImGui::ShowDemoWindow(&bOpen);
}

void UImGuiBPFunctionLibrary::ShowMetricsWindow(bool& bOpen)
{
	ImGui::ShowMetricsWindow(&bOpen);
}

void UImGuiBPFunctionLibrary::ShowDebugLogWindow(bool& bOpen)
{
	ImGui::ShowDebugLogWindow(&bOpen);
}

void UImGuiBPFunctionLibrary::ShowIDStackToolWindow(bool& bOpen)
{
	ImGui::ShowIDStackToolWindow(&bOpen);
}

void UImGuiBPFunctionLibrary::ShowAboutWindow(bool& bOpen)
{
	ImGui::ShowAboutWindow(&bOpen);
}

//void UImGuiBPFunctionLibrary::ShowStyleEditor(ImGuiStyle* ref = NULL)

bool UImGuiBPFunctionLibrary::ShowStyleSelector(FString Label)
{
	auto label = StringCast<ANSICHAR>(*Label);
	return ImGui::ShowStyleSelector(label.Get());
}

void UImGuiBPFunctionLibrary::ShowFontSelector(FString Label)
{
	auto label = StringCast<ANSICHAR>(*Label);
	ImGui::ShowFontSelector(label.Get());
}

void UImGuiBPFunctionLibrary::ShowUserGuide()
{
	ImGui::ShowUserGuide();
}

FString UImGuiBPFunctionLibrary::GetVersion()
{
	auto version = StringCast<TCHAR>(ImGui::GetVersion());
	return version.Get();
}


// Styles

// ==== Windows ====

bool UImGuiBPFunctionLibrary::BeginMainWindow(FString Name, int WindowFlagsBitmask, bool bClosable, bool& bOpen)
{
	bool* bOpenConverted = bClosable
		? &bOpen
		: nullptr;

	if (!bClosable || bOpen)
	{
		auto name = StringCast<ANSICHAR>(*Name);
		return ImGui::Begin(name.Get(), bOpenConverted, WindowFlagsBitmask);
	}
	else
	{
		return false;
	}
}

void UImGuiBPFunctionLibrary::EndMainWindow()
{
	ImGui::End();
}

// ==== Child Windows ====

bool UImGuiBPFunctionLibrary::BeginChild(FString HashName, FVector2D Size, bool bBorder, int WindowFlagsBitmask)
{
	int HashId = GetTypeHash(HashName);
	ImVec2 SizeInPixels = GetScreenSizeInPixels(Size);

	return ImGui::BeginChild(HashId, SizeInPixels, bBorder, WindowFlagsBitmask);
}

void UImGuiBPFunctionLibrary::EndChild()
{
	ImGui::EndChild();
}

// ==== Windows Utilities ====

bool UImGuiBPFunctionLibrary::IsWindowCollapsed()
{
	return ImGui::IsWindowCollapsed();
}

bool UImGuiBPFunctionLibrary::IsWindowFocused()
{
	return ImGui::IsWindowFocused(ImGuiFocusedFlags_None);
}

bool UImGuiBPFunctionLibrary::IsWindowHovered()
{
	return ImGui::IsWindowHovered(ImGuiFocusedFlags_None);
}

FVector2D UImGuiBPFunctionLibrary::GetWindowPosition(bool bRelative)
{
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ImVec2 WindowPositionRaw;
	FVector2D  WindowPositionFixed;

	WindowPositionRaw = ImGui::GetWindowPos();
	WindowPositionFixed.X = bRelative
		? WindowPositionRaw.x / ViewportSize.X
		: WindowPositionRaw.x;
	WindowPositionFixed.Y = bRelative
		? WindowPositionRaw.y / ViewportSize.Y
		: WindowPositionRaw.y;

	return  WindowPositionFixed;
}

FVector2D UImGuiBPFunctionLibrary::GetWindowSize(bool bRelative)
{
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ImVec2 WindowSizeRaw;
	FVector2D  WindowSizeFixed;

	WindowSizeRaw = ImGui::GetWindowSize();
	WindowSizeFixed.X = bRelative
		? WindowSizeRaw.x / ViewportSize.X
		: WindowSizeRaw.x;
	WindowSizeFixed.Y = bRelative
		? WindowSizeRaw.y / ViewportSize.Y
		: WindowSizeRaw.y;

	return  WindowSizeFixed;
}

// ==== Window manipulation ====

void UImGuiBPFunctionLibrary::SetNextWindowScreenPosition(FVector2D ScreenPosition, EImGuiConditions Condition)
{
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ImVec2 WindowPosition = GetScreenSizeInPixels(ScreenPosition);
	ImVec2 WindowPivot = GetRelativeScreenPosition(ScreenPosition);

	// avoids a call when the viewport is being created
	if (ViewportSize.X > 0 && ViewportSize.Y > 0)
	{
		ImGui::SetNextWindowPos(WindowPosition, (ImGuiCond)Condition, WindowPivot);
	}
}

void UImGuiBPFunctionLibrary::SetNextWindowSize(FVector2D Size, EImGuiConditions Condition)
{
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ImVec2 SizeConverted = GetScreenSizeInPixels(Size);

	// avoids a call when the viewport is being created
	if (ViewportSize.X > 0 && ViewportSize.Y > 0)
	{
		ImGui::SetNextWindowSize(SizeConverted, (ImGuiCond)Condition);
	}
}

void UImGuiBPFunctionLibrary::SetNextWindowSizeConstraints(FVector2D SizeMin, FVector2D SizeMax)
{
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ImVec2 SizeMinConverted = GetScreenSizeInPixels(SizeMin);
	ImVec2 SizeMaxConverted = GetScreenSizeInPixels(SizeMax);

	// don't call when viewport is just begin created
	if (ViewportSize.X > 0 && ViewportSize.Y > 0)
	{
		ImGui::SetNextWindowSizeConstraints(SizeMinConverted, SizeMaxConverted);
	}
}

void UImGuiBPFunctionLibrary::SetNextWindowContentSize(FVector2D Size)
{
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ImVec2 SizeConverted = GetScreenSizeInPixels(Size);;

	// don't call when viewport is just begin created
	if (ViewportSize.X > 0 && ViewportSize.Y > 0)
	{
		ImGui::SetNextWindowContentSize(SizeConverted);
	}
}

void UImGuiBPFunctionLibrary::SetNextWindowCollapsed(bool bCollapsed, EImGuiConditions Condition)
{
	ImGui::SetNextWindowCollapsed(bCollapsed, (ImGuiCond)Condition);
}

void UImGuiBPFunctionLibrary::SetNextWindowFocused()
{
	ImGui::SetNextWindowFocus();
}

void UImGuiBPFunctionLibrary::SetNextWindowBackgroundAlpha(float BackgroundAlpha)
{
	ImGui::SetNextWindowBgAlpha(BackgroundAlpha);
}

void UImGuiBPFunctionLibrary::SetWindowFontScale(float Scale)
{
	ImGui::SetWindowFontScale(Scale);
}

// ==== Content region ====

FVector2f UImGuiBPFunctionLibrary::GetContentRegionAvail()
{
	ImVec2 result = ImGui::GetContentRegionAvail();
	return FVector2f{ result.x, result.y };
}

FVector2f UImGuiBPFunctionLibrary::GetContentRegionMax()
{
	ImVec2 result = ImGui::GetContentRegionMax();
	return FVector2f{ result.x, result.y };
}

FVector2f UImGuiBPFunctionLibrary::GetWindowContentRegionMin()
{
	ImVec2 result = ImGui::GetWindowContentRegionMin();
	return FVector2f{ result.x, result.y };
}

FVector2f UImGuiBPFunctionLibrary::GetWindowContentRegionMax()
{
	ImVec2 result = ImGui::GetWindowContentRegionMax();
	return FVector2f{ result.x, result.y };
}

// ==== Windows Scrolling ====

float UImGuiBPFunctionLibrary::GetScrollX()
{
	return ImGui::GetScrollX();
}

float UImGuiBPFunctionLibrary::GetScrollY()
{
	return ImGui::GetScrollY();
}

void UImGuiBPFunctionLibrary::SetScrollX(float ScrollX)
{
	ImGui::SetScrollX(ScrollX);
}

void UImGuiBPFunctionLibrary::SetScrollY(float ScrollY)
{
	ImGui::SetScrollY(ScrollY);
}

float UImGuiBPFunctionLibrary::GetScrollMaxX()
{
	return ImGui::GetScrollMaxX();
}

float UImGuiBPFunctionLibrary::GetScrollMaxY()
{
	return ImGui::GetScrollMaxY();
}

void UImGuiBPFunctionLibrary::SetScrollHereX(float CenterXRatio)
{
	ImGui::SetScrollHereX(CenterXRatio);
}

void UImGuiBPFunctionLibrary::SetScrollHereY(float CenterYRatio)
{
	ImGui::SetScrollHereY(CenterYRatio);
}

void UImGuiBPFunctionLibrary::SetScrollFromPosX(float LocalX, float CenterXRatio)
{
	ImGui::SetScrollFromPosX(LocalX, CenterXRatio);
}

void UImGuiBPFunctionLibrary::SetScrollFromPosY(float LocalY, float CenterYRatio)
{
	ImGui::SetScrollFromPosY(LocalY, CenterYRatio);
}

// Parameters stacks (shared)
// Parameters stacks (current window)
// Style read access

// ==== Cursor / Layout ====

void UImGuiBPFunctionLibrary::AddSeparator()
{
	ImGui::Separator();
}

void UImGuiBPFunctionLibrary::StayInSameLine()
{
	ImGui::SameLine();
}

void UImGuiBPFunctionLibrary::AddSpacing()
{
	ImGui::Spacing();
}

void UImGuiBPFunctionLibrary::AddDummy(FVector2D Size)
{
	ImVec2 SizeInPixels = GetScreenSizeInPixels(Size);

	ImGui::Dummy(SizeInPixels);
}

void UImGuiBPFunctionLibrary::Indent(float ToRight)
{
	ImGui::Indent(ToRight);
}

void UImGuiBPFunctionLibrary::BeginGroup()
{
	ImGui::BeginGroup();
}

void UImGuiBPFunctionLibrary::EndGroup()
{
	ImGui::EndGroup();
}

// ID stack/scopes

// ==== Widgets / Text ====

void UImGuiBPFunctionLibrary::AddText(FString Text)
{
	auto text = StringCast<ANSICHAR>(*Text);
	ImGui::Text("%s", text.Get());
}

// ==== Widgets / Main ====

bool UImGuiBPFunctionLibrary::Button(FString Label, FVector2D Size)
{
	ImVec2 SizeInPixels = GetScreenSizeInPixels(Size);

	auto label = StringCast<ANSICHAR>(*Label);
	return ImGui::Button(label.Get(), SizeInPixels);
}

bool UImGuiBPFunctionLibrary::SmallButton(FString Label)
{
	auto label = StringCast<ANSICHAR>(*Label);
	return ImGui::SmallButton(label.Get());
}

bool UImGuiBPFunctionLibrary::InvisibleButton(FString HashName, FVector2D Size)
{
	ImVec2 SizeInPixels = GetScreenSizeInPixels(Size);

	auto hashName = StringCast<ANSICHAR>(*HashName);
	return ImGui::InvisibleButton(hashName.Get(), SizeInPixels);
}

bool UImGuiBPFunctionLibrary::ArrowButton(FString HashName, EImGuiDirectionType Direction)
{
	auto hashName = StringCast<ANSICHAR>(*HashName);
	return ImGui::ArrowButton(hashName.Get(), (ImGuiDir)Direction - 1);
}

bool UImGuiBPFunctionLibrary::Checkbox(FString Label, bool& CheckedBool)
{
	auto label = StringCast<ANSICHAR>(*Label);
	return ImGui::Checkbox(label.Get(), &CheckedBool);
}

bool UImGuiBPFunctionLibrary::RadioButton(FString Label, bool bActive)
{
	auto label = StringCast<ANSICHAR>(*Label);
	return ImGui::RadioButton(label.Get(), bActive);
}

bool UImGuiBPFunctionLibrary::RadioButtonList(TSet<FString> Labels, int& RadioedIntiger)
{
	bool bRadioedIntegerChanged = false;
	int LabelIterator = 0;

	for (FString Label : Labels)
	{
		auto label = StringCast<ANSICHAR>(*Label);
		if (ImGui::RadioButton(label.Get(), &RadioedIntiger, LabelIterator))
		{
			// this must be changed at branch, otherwise other buttons will set bRadioedIntegerChanged back to false
			bRadioedIntegerChanged = true;
		}
		LabelIterator++;
	}

	return bRadioedIntegerChanged;
}

void UImGuiBPFunctionLibrary::AddProgressBar(float Fraction, FVector2D Size, FString Overlay)
{
	ImVec2 SizeInPixels = GetScreenSizeInPixels(Size);

	auto overlay = StringCast<ANSICHAR>(*Overlay);
	const char* progressOverlay = Overlay.IsEmpty()
		? nullptr
		: overlay.Get();
	ImGui::ProgressBar(Fraction, SizeInPixels, progressOverlay);
}

void UImGuiBPFunctionLibrary::AddBullet()
{
	ImGui::Bullet();
}

// ==== Widgets: Combo Box ====

bool UImGuiBPFunctionLibrary::BeginCombo(FString Label, FString Preview)
{
	auto label = StringCast<ANSICHAR>(*Label);
	auto preview = StringCast<ANSICHAR>(*Preview);
	return ImGui::BeginCombo(label.Get(), preview.Get());
}

void UImGuiBPFunctionLibrary::EndCombo()
{
	ImGui::EndCombo();
}

// Widgets: Drag Sliders

bool UImGuiBPFunctionLibrary::AddDragFloatArray(FString Label, TArray<float>& DraggedArrayReference, float DragSpeed, float MinValue, float MaxValue)
{
	int ItemsAmount = DraggedArrayReference.Num();
	float* PassByRefArray = new float[ItemsAmount];
	for (int i = 0; i < ItemsAmount; i++)
	{
		PassByRefArray[i] = DraggedArrayReference[i];
	}

	auto label = StringCast<ANSICHAR>(*Label);
	bool bChanged = ImGui::DragScalarN(label.Get(), ImGuiDataType_Float, PassByRefArray, ItemsAmount, DragSpeed, &MinValue, &MaxValue);
	for (int i = 0; i < ItemsAmount; i++)
	{
		DraggedArrayReference[i] = PassByRefArray[i];
	}

	delete[] PassByRefArray;
	return bChanged;
}

bool UImGuiBPFunctionLibrary::AddDragIntArray(FString Label, TArray<int>& DraggedArrayReference, float DragSpeed, int MinValue, int MaxValue)
{

	int ItemsAmount = DraggedArrayReference.Num();
	int* PassByRefArray = new int[ItemsAmount];
	for (int i = 0; i < ItemsAmount; i++)
	{
		PassByRefArray[i] = DraggedArrayReference[i];
	}

	auto label = StringCast<ANSICHAR>(*Label);
	bool bChanged = ImGui::DragScalarN(label.Get(), ImGuiDataType_S32, PassByRefArray, ItemsAmount, DragSpeed, &MinValue, &MaxValue);
	for (int i = 0; i < ItemsAmount; i++)
	{
		DraggedArrayReference[i] = PassByRefArray[i];
	}

	delete[] PassByRefArray;
	return bChanged;
}

// ==== Widgets / Regular Sliders ====

bool UImGuiBPFunctionLibrary::AddSliderFloatArray(FString Label, TArray<float>& SlidedArrayReference, float MinValue, float MaxValue)
{
	int ItemsAmount = SlidedArrayReference.Num();
	float* PassByRefArray = new float[ItemsAmount];
	for (int i = 0; i < ItemsAmount; i++)
	{
		PassByRefArray[i] = SlidedArrayReference[i];
	}

	auto label = StringCast<ANSICHAR>(*Label);
	bool bChanged = ImGui::SliderScalarN(label.Get(), ImGuiDataType_Float, PassByRefArray, ItemsAmount, &MinValue, &MaxValue);
	for (int i = 0; i < ItemsAmount; i++)
	{
		SlidedArrayReference[i] = PassByRefArray[i];
	}

	delete[] PassByRefArray;
	return bChanged;
}

bool UImGuiBPFunctionLibrary::AddSliderIntArray(FString Label, TArray<int>& SlidedArrayReference, int MinValue, int MaxValue)
{
	int ItemsAmount = SlidedArrayReference.Num();
	int* PassByRefArray = new int[ItemsAmount];
	for (int i = 0; i < ItemsAmount; i++)
	{
		PassByRefArray[i] = SlidedArrayReference[i];
	}

	auto label = StringCast<ANSICHAR>(*Label);
	bool bChanged = ImGui::SliderScalarN(label.Get(), ImGuiDataType_S32, PassByRefArray, ItemsAmount, &MinValue, &MaxValue);
	for (int i = 0; i < ItemsAmount; i++)
	{
		SlidedArrayReference[i] = PassByRefArray[i];
	}

	delete[] PassByRefArray;
	return bChanged;
}

// ==== Widgets: Input with Keyboard ====

namespace ImGui
{
	IMGUI_API bool InputTextEx(const char* label, const char* hint, char* buf, int buf_size, const ImVec2& size_arg, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* callback_user_data);
}

bool UImGuiBPFunctionLibrary::AddInputTextBox(FString Label, FString Hint, UPARAM(ref) FString& InputedString, int MaxCharactersCount, FVector2D BoxSize, int InputTextFlagsBitmask)
{
	auto inputedString = StringCast<ANSICHAR>(*InputedString);
	TArray<ANSICHAR> InputedStringConverted(inputedString.Get(), InputedString.Len());
	if (MaxCharactersCount != 0)
	{
		InputedStringConverted.SetNumZeroed(MaxCharactersCount);
	}
	ImVec2 BoxSizeConverted = GetScreenSizeInPixels(BoxSize);

	// we can't pass in ImGuiInputTextFlags_CallbackResize without also providing a callback function
	ImGuiInputTextFlags reducedFlags = (ImGuiInputTextFlags)InputTextFlagsBitmask & (~ImGuiInputTextFlags_CallbackResize);
	auto label = StringCast<ANSICHAR>(*Label);
	auto hint = StringCast<ANSICHAR>(*Hint);
	bool bCallback = ImGui::InputTextEx(label.Get(), hint.Get(), InputedStringConverted.GetData(), InputedStringConverted.Num(), BoxSizeConverted, reducedFlags, nullptr, nullptr);

	auto text = StringCast<TCHAR>(InputedStringConverted.GetData(), InputedStringConverted.Num());
	InputedString = text.Get();
	return bCallback;
}

// Widgets: Color Editor/Picker (tip: the ColorEdit* functions have a little color square that can be left-clicked to open a picker, and right-clicked to open an option menu.)
// ==== Widgets / Trees ====

bool UImGuiBPFunctionLibrary::TreeNode(FString Label)
{
	auto label = StringCast<ANSICHAR>(*Label);
	return ImGui::TreeNode(label.Get());
}

bool UImGuiBPFunctionLibrary::CollapsingHeader(FString Label)
{
	auto label = StringCast<ANSICHAR>(*Label);
	return ImGui::CollapsingHeader(label.Get());
}

void UImGuiBPFunctionLibrary::SetNextItemOpen(bool bOpen, EImGuiConditions Condition)
{
	ImGui::SetNextItemOpen(bOpen, (ImGuiCond)Condition);
}

// ==== Widgets / Selectables ====

bool UImGuiBPFunctionLibrary::Selectable(FString Label, bool& bSelected, FVector2D Size)
{
	ImVec2 SizeConverted = GetScreenSizeInPixels(Size);

	auto label = StringCast<ANSICHAR>(*Label);
	return ImGui::Selectable(label.Get(), &bSelected, ImGuiSelectableFlags_None, SizeConverted);
}

// ==== Widgets / List Boxes ====

bool UImGuiBPFunctionLibrary::BeginListBox(FString Label, FVector2D Size)
{
	ImVec2 SizeConverted = GetScreenSizeInPixels(Size);

	auto label = StringCast<ANSICHAR>(*Label);
	return ImGui::BeginListBox(label.Get(), SizeConverted);
}

void UImGuiBPFunctionLibrary::EndListBox()
{
	ImGui::EndListBox();
}

// Widgets: Data Plotting
// Widgets: Value() Helpers.
// ==== Widgets / Menus ====

bool UImGuiBPFunctionLibrary::BeginMenuBar()
{
	return ImGui::BeginMenuBar();
}

void UImGuiBPFunctionLibrary::EndMenuBar()
{
	ImGui::EndMenuBar();
}

bool UImGuiBPFunctionLibrary::BeginMainMenuBar()
{
	return ImGui::BeginMainMenuBar();
}

void UImGuiBPFunctionLibrary::EndMainMenuBar()
{
	ImGui::EndMainMenuBar();
}

bool UImGuiBPFunctionLibrary::BeginMenu(FString Label, bool bEnabled)
{
	auto label = StringCast<ANSICHAR>(*Label);
	return ImGui::BeginMenu(label.Get(), bEnabled);
}

void UImGuiBPFunctionLibrary::EndMenu()
{
	ImGui::EndMenu();
}

bool UImGuiBPFunctionLibrary::MenuItem(FString Label, FString Shortcut, bool& bSelected, bool bEnabled)
{
	auto label = StringCast<ANSICHAR>(*Label);
	auto shortcut = StringCast<ANSICHAR>(*Shortcut);
	return ImGui::MenuItem(label.Get(), shortcut.Get(), &bSelected, bEnabled);
}

// ==== Tooltips ====

void UImGuiBPFunctionLibrary::BeginTooltip()
{
	ImGui::BeginTooltip();
}

void UImGuiBPFunctionLibrary::EndTooltip()
{
	ImGui::EndTooltip();
}

// ==== Popups / begin/end functions ====

bool UImGuiBPFunctionLibrary::BeginPopup(FString HashName, int WindowFlagsBitmask)
{
	auto hashName = StringCast<ANSICHAR>(*HashName);
	return ImGui::BeginPopup(hashName.Get(), WindowFlagsBitmask);
}

bool UImGuiBPFunctionLibrary::BeginPopupModal(FString Name, bool bClosable, UPARAM(ref) bool& bOpenModal, int WindowFlagsBitmask)
{
	bool* bOpenConverted = bClosable
		? &bOpenModal
		: nullptr;
	auto name = StringCast<ANSICHAR>(*Name);
	return ImGui::BeginPopupModal(name.Get(), bOpenConverted, WindowFlagsBitmask);
}

void UImGuiBPFunctionLibrary::EndPopup()
{
	ImGui::EndPopup();
}

void UImGuiBPFunctionLibrary::OpenPopup(FString HashName)
{
	// XXX: add support for other mouse button(s)?
	if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
	{
		auto hashName = StringCast<ANSICHAR>(*HashName);
		ImGui::OpenPopup(hashName.Get(), ImGuiPopupFlags_MouseButtonLeft);
	}
}

void UImGuiBPFunctionLibrary::CloseCurrentPopup()
{
	ImGui::CloseCurrentPopup();
}

bool UImGuiBPFunctionLibrary::IsPopupOpen(FString HashName)
{
	auto hashName = StringCast<ANSICHAR>(*HashName);
	return ImGui::IsPopupOpen(hashName.Get(), ImGuiPopupFlags_MouseButtonLeft);
}

// Popups: open/close functions
// Popups: open+begin combined functions helpers
// Popups: query functions
// ==== Tables ====

bool UImGuiBPFunctionLibrary::BeginTable(FString HashName, int Column, FVector2D OuterSize, float InnerWidth)
{
	ImVec2 OuterSizeConverted = GetScreenSizeInPixels(OuterSize);

	auto hashName = StringCast<ANSICHAR>(*HashName);
	return ImGui::BeginTable(hashName.Get(), Column, ImGuiTableFlags_None, OuterSizeConverted, InnerWidth);
}

void UImGuiBPFunctionLibrary::EndTable()
{
	ImGui::EndTable();
}

void UImGuiBPFunctionLibrary::TableNextRow(float MinRowHeight)
{
	ImGui::TableNextRow(ImGuiTableRowFlags_None, MinRowHeight);
}

bool UImGuiBPFunctionLibrary::TableNextColumn()
{
	return ImGui::TableNextColumn();
}

bool UImGuiBPFunctionLibrary::TableSetColumnIndex(int Column)
{
	return ImGui::TableSetColumnIndex(Column);
}

void UImGuiBPFunctionLibrary::TableHeader(FString Label)
{
	auto label = StringCast<ANSICHAR>(*Label);
	ImGui::TableHeader(label.Get());
}

// Tables: Headers & Columns declaration
// Tables: Sorting
// Tables: Miscellaneous functions
// Legacy Columns API (prefer using Tables!)
// ==== Tab Bars, Tabs ====

bool UImGuiBPFunctionLibrary::BeginTabBar(FString HashName)
{
	auto hashName = StringCast<ANSICHAR>(*HashName);
	return ImGui::BeginTabBar(hashName.Get());
}

void UImGuiBPFunctionLibrary::EndTabBar()
{
	ImGui::EndTabBar();
}

bool UImGuiBPFunctionLibrary::BeginTabItem(FString Label, bool bClosable, bool& bOpen)
{
	bool* bOpenConverted = bClosable
		? &bOpen
		: nullptr;

	auto label = StringCast<ANSICHAR>(*Label);
	return ImGui::BeginTabItem(label.Get(), bOpenConverted);
}

void UImGuiBPFunctionLibrary::EndTabItem()
{
	ImGui::EndTabItem();
}

bool UImGuiBPFunctionLibrary::TabItemButton(FString Label)
{
	auto label = StringCast<ANSICHAR>(*Label);
	return ImGui::TabItemButton(label.Get(), 0);
}

void UImGuiBPFunctionLibrary::SetNextTabItemClosed(FString Label)
{
	auto label = StringCast<ANSICHAR>(*Label);
	ImGui::SetTabItemClosed(label.Get());
}



// Logging/Capture

// ==== Drag and Drop ====

bool UImGuiBPFunctionLibrary::BeginDragDropSource()
{
	return ImGui::BeginDragDropSource(ImGuiDragDropFlags_None);
}

bool UImGuiBPFunctionLibrary::SetDragDropPayload(FString HashName)
{
	auto hashName = StringCast<ANSICHAR>(*HashName);
	return ImGui::SetDragDropPayload(hashName.Get(), nullptr, ImGuiCond_None);
}

void UImGuiBPFunctionLibrary::EndDragDropSource()
{
	ImGui::EndDragDropSource();
}

bool UImGuiBPFunctionLibrary::BeginDragDropTarget()
{
	return ImGui::BeginDragDropTarget();
}

bool UImGuiBPFunctionLibrary::AcceptDragDropPayload(FString HashName)
{
	const ImGuiPayload* Payload;

	auto hashName = StringCast<ANSICHAR>(*HashName);
	Payload = ImGui::AcceptDragDropPayload(hashName.Get(), ImGuiDragDropFlags_None);
	return (Payload != nullptr);
}

void UImGuiBPFunctionLibrary::EndDragDropTarget()
{
	ImGui::EndDragDropTarget();
}



// ==== Disabling [BETA API] ====

void UImGuiBPFunctionLibrary::BeginDisabled(bool bDisabled)
{
	ImGui::BeginDisabled(bDisabled);
}

void UImGuiBPFunctionLibrary::EndDisabled()
{
	ImGui::EndDisabled();
}

// Clipping
// Focus, Activation
// Item/Widgets Utilities and Query Functions
// Viewports
// Miscellaneous Utilities
// Text Utilities
// Color Utilities
// Inputs Utilities: Keyboard
// Inputs Utilities: Mouse
// Clipboard Utilities
// Settings/.Ini Utilities
// Debug Utilities
// Memory Allocators


//Private

ImVec2 UImGuiBPFunctionLibrary::GetScreenSizeInPixels(FVector2D ScreenSize)
{
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ImVec2 Pixels;

	Pixels.x = (ScreenSize.X < 0 || ScreenSize.X > ViewportSize.X)
		? 0
		: (ScreenSize.X <= 1)
			? ScreenSize.X * ViewportSize.X
			: ScreenSize.X;
	Pixels.y = (ScreenSize.Y < 0 || ScreenSize.Y > ViewportSize.Y)
		? 0
		: (ScreenSize.Y <= 1)
			? ScreenSize.Y * ViewportSize.Y
			: ScreenSize.Y;

	return Pixels;
}

ImVec2 UImGuiBPFunctionLibrary::GetRelativeScreenPosition(FVector2D ScreenSize)
{
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ImVec2 RelativePosition;

	RelativePosition.x = (ScreenSize.X < 0 || ScreenSize.X > ViewportSize.X)
		? 0
		: (ScreenSize.X <= 1)
			? ScreenSize.X
			: ScreenSize.X / ViewportSize.X;
	RelativePosition.y = (ScreenSize.Y < 0 || ScreenSize.Y > ViewportSize.Y)
		? 0
		: (ScreenSize.Y <= 1)
			? ScreenSize.Y
			: ScreenSize.Y / ViewportSize.Y;

	return RelativePosition;
}
