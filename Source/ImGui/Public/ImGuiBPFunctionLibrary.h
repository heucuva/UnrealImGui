// Distributed under the MIT License (MIT) (see accompanying LICENSE file)

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc/Optional.h"
#include "ImGuiEnums.h"
#include "ImGuiBPFunctionLibrary.generated.h"

struct ImVec2;

UCLASS()
class IMGUI_API UImGuiBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Context creation and access

	// ==== Main ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|HUD", BlueprintCosmetic)
		static void SetShowingImgui(bool Showing);

	UFUNCTION(BlueprintCallable, Category = "Imgui|HUD", BlueprintCosmetic)
		static UPARAM(DisplayName = "bShowing") bool IsShowingImgui();

	UFUNCTION(BlueprintCallable, Category = "Imgui|HUD", BlueprintCosmetic)
		static void ToggleShowingImgui();

	// ==== Demo, Debug, Information ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Demo", meta = (AutoCreateRefTerm = "bOpen"), BlueprintCosmetic)
		static void ShowDemoWindow(bool& bOpen);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Debug", meta = (AutoCreateRefTerm = "bOpen"), BlueprintCosmetic)
		static void ShowMetricsWindow(bool& bOpen);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Debug", meta = (AutoCreateRefTerm = "bOpen"), BlueprintCosmetic)
		static void ShowDebugLogWindow(bool& bOpen);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Debug", meta = (AutoCreateRefTerm = "bOpen"), BlueprintCosmetic)
		static void ShowIDStackToolWindow(bool& bOpen);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Information", meta = (AutoCreateRefTerm = "bOpen"), BlueprintCosmetic)
		static void ShowAboutWindow(bool& bOpen);

	// TODO: add Style support
	//UFUNCTION(BlueprintCallable, Category = "Imgui|Debug", BlueprintCosmetic)
	//	static void ShowStyleEditor(ImGuiStyle* ref = NULL);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Debug", BlueprintCosmetic)
		static UPARAM(DisplayName = "bValid") bool ShowStyleSelector(FString Label);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Debug", BlueprintCosmetic)
		static void ShowFontSelector(FString Label);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Information", BlueprintCosmetic)
		static void ShowUserGuide();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Information", BlueprintCosmetic)
		static FString GetVersion();

	// Styles

	// ==== Windows ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window", meta = (AutoCreateRefTerm = "bOpen"), BlueprintCosmetic, DisplayName = "Begin")
		static UPARAM(DisplayName = "bOpen") bool BeginMainWindow(FString Name, UPARAM(meta = (Bitmask, BitmaskEnum = "/Script/ImGui.EImGuiWindowFlags")) int WindowFlagsBitmask, bool bClosable, UPARAM(ref) bool& bOpen);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window", BlueprintCosmetic, DisplayName = "End")
		static void EndMainWindow();

	// ==== Child Windows ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Child", BlueprintCosmetic)
		static UPARAM(DisplayName = "bVisible") bool BeginChild(FString HashName, FVector2D Size, bool bBorder, UPARAM(meta = (Bitmask, BitmaskEnum = "/Script/ImGui.EImGuiWindowFlags")) int WindowFlagsBitmask);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Child", BlueprintCosmetic)
		static void EndChild();

	// ==== Windows Utilities ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window", BlueprintCosmetic)
		static UPARAM(DisplayName = "bCollapsed") bool IsWindowCollapsed();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window", BlueprintCosmetic)
		static UPARAM(DisplayName = "bFocused") bool IsWindowFocused();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window", BlueprintCosmetic)
		static UPARAM(DisplayName = "bHovered") bool IsWindowHovered();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window", BlueprintCosmetic)
		static UPARAM(DisplayName = "Position") FVector2D GetWindowPosition(bool bRelative = false);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window", BlueprintCosmetic)
		static UPARAM(DisplayName = "Size") FVector2D GetWindowSize(bool bRelative = false);

	// ==== Window manipulation ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Manipulation", BlueprintCosmetic)
		static void SetNextWindowScreenPosition(FVector2D ScreenPosition, EImGuiConditions Condition = EImGuiConditions::Always);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Manipulation", BlueprintCosmetic)
		static void SetNextWindowSize(FVector2D Size, EImGuiConditions Condition = EImGuiConditions::Always);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Manipulation", BlueprintCosmetic)
		static void SetNextWindowSizeConstraints(FVector2D SizeMin, FVector2D SizeMax);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Manipulation", BlueprintCosmetic)
		static void SetNextWindowContentSize(FVector2D Size);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Manipulation", BlueprintCosmetic)
		static void SetNextWindowCollapsed(bool bCollapsed, EImGuiConditions Condition = EImGuiConditions::Always);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Manipulation", BlueprintCosmetic)
		static void SetNextWindowFocused();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Manipulation", BlueprintCosmetic)
		static void SetNextWindowBackgroundAlpha(float BackgroundAlpha);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Manipulation", BlueprintCosmetic)
		static void SetWindowFontScale(float Scale = 1);

	// ==== Content region ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|ContentRegion", BlueprintCosmetic)
		static FVector2f GetContentRegionAvail();

	UFUNCTION(BlueprintCallable, Category = "Imgui|ContentRegion", BlueprintCosmetic)
		static FVector2f GetContentRegionMax();
	
	UFUNCTION(BlueprintCallable, Category = "Imgui|ContentRegion", BlueprintCosmetic)
		static FVector2f GetWindowContentRegionMin();
	
	UFUNCTION(BlueprintCallable, Category = "Imgui|ContentRegion", BlueprintCosmetic)
		static FVector2f GetWindowContentRegionMax();

	// ==== Windows Scrolling ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Scrolling", BlueprintCosmetic)
		static float GetScrollX();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Scrolling", BlueprintCosmetic)
		static float GetScrollY();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Scrolling", BlueprintCosmetic)
		static void SetScrollX(float ScrollX);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Scrolling", BlueprintCosmetic)
		static void SetScrollY(float ScrollY);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Scrolling", BlueprintCosmetic)
		static float GetScrollMaxX();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Scrolling", BlueprintCosmetic)
		static float GetScrollMaxY();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Scrolling", BlueprintCosmetic)
		static void SetScrollHereX(float CenterXRatio = 0.5f);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Scrolling", BlueprintCosmetic)
		static void SetScrollHereY(float CenterYRatio = 0.5f);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Scrolling", BlueprintCosmetic)
		static void SetScrollFromPosX(float LocalX, float CenterXRatio = 0.5f);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Window|Scrolling", BlueprintCosmetic)
		static void SetScrollFromPosY(float LocalY, float CenterYRatio = 0.5f);
	
	// Parameters stacks (shared)
	// Parameters stacks (current window)
	// Style read access

	// ==== Cursor / Layout ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Layout", BlueprintCosmetic)
		static void AddSeparator();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Layout", BlueprintCosmetic)
		static void StayInSameLine();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Layout", BlueprintCosmetic)
		static void AddSpacing();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Layout", BlueprintCosmetic)
		static void AddDummy(FVector2D Size);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Layout", BlueprintCosmetic)
		static void Indent(float ToRight = 0);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Layout", BlueprintCosmetic)
		static void BeginGroup();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Layout", BlueprintCosmetic)
		static void EndGroup();

	// ID stack/scopes

	// ==== Widgets / Text ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets", BlueprintCosmetic)
		static void AddText(FString Text);

	// ==== Widgets / Main ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets", BlueprintCosmetic)
		static UPARAM(DisplayName = "bClicked") bool Button(FString Label, FVector2D Size);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets", BlueprintCosmetic)
		static UPARAM(DisplayName = "bClicked") bool SmallButton(FString Label);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets", BlueprintCosmetic)
		static UPARAM(DisplayName = "bClicked") bool InvisibleButton(FString HashName, FVector2D Size);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets", BlueprintCosmetic)
		static UPARAM(DisplayName = "bClicked") bool ArrowButton(FString HashName, EImGuiDirectionType Direction);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets", BlueprintCosmetic)
		static UPARAM(DisplayName = "bChanged") bool Checkbox(FString Label, UPARAM(ref) bool& CheckedBool);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets", BlueprintCosmetic)
		static UPARAM(DisplayName = "bClicked") bool RadioButton(FString Label, bool bActive);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets", BlueprintCosmetic)
		static UPARAM(DisplayName = "bClicked") bool RadioButtonList(TSet<FString> Labels, UPARAM(ref) int& RadioedIntiger);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets", BlueprintCosmetic)
		static void AddProgressBar(float Fraction, FVector2D Size, FString Overlay);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets", BlueprintCosmetic)
		static void AddBullet();

	// ==== Widgets / Combo Box ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|ComboBox", BlueprintCosmetic)
		static UPARAM(DisplayName = "bOpen") bool BeginCombo(FString Label, FString Preview);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|ComboBox", BlueprintCosmetic)
		static void EndCombo();

	// ==== Widgets / Drag Sliders ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|DragSlider", BlueprintCosmetic)
		static UPARAM(DisplayName = "bChanged") bool AddDragFloatArray(FString Label, UPARAM(ref) TArray<float>& DraggedArrayReference, float DragSpeed = 1.0f, float MinValue = 0.0f, float MaxValue = 0.0f);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|DragSlider", BlueprintCosmetic)
		static UPARAM(DisplayName = "bChanged") bool AddDragIntArray(FString Label, UPARAM(ref) TArray<int>& DraggedArrayReference, float DragSpeed = 1.0f, int MinValue = 0, int MaxValue = 0);

	// ==== Widgets / Regular Sliders ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|RegularSlider", BlueprintCosmetic)
		static UPARAM(DisplayName = "bChanged") bool AddSliderFloatArray(FString Label, UPARAM(ref) TArray<float>& SlidedArrayReference, float MinValue = 0.0f, float MaxValue = 100.0f);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|RegularSlider", BlueprintCosmetic)
		static UPARAM(DisplayName = "bChanged") bool AddSliderIntArray(FString Label, UPARAM(ref) TArray<int>& SlidedArrayReference, int MinValue = 0, int MaxValue = 100);


	// ==== Widgets / Input with Keyboard ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|Input", BlueprintCosmetic)
		static UPARAM(DisplayName = "bCallback") bool AddInputTextBox(FString Label, FString Hint, UPARAM(ref) FString& InputedString, int MaxCharactersCount, FVector2D BoxSize, UPARAM(meta = (Bitmask, BitmaskEnum = "/Script/ImGui.EImGuiInputTextFlags")) int InputTextFlagsBitmask);

	// Widgets: Color Editor/Picker (tip: the ColorEdit* functions have a little color square that can be left-clicked to open a picker, and right-clicked to open an option menu.)
	// ==== Widgets / Trees ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|Tree", BlueprintCosmetic)
		static UPARAM(DisplayName = "bOpen") bool TreeNode(FString Label);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|Tree", BlueprintCosmetic)
		static UPARAM(DisplayName = "bOpen") bool CollapsingHeader(FString Label);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|Tree", BlueprintCosmetic)
		static void SetNextItemOpen(bool bOpen = true, EImGuiConditions Condition = EImGuiConditions::Always);

	// ==== Widgets / Selectables ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets", meta = (AutoCreateRefTerm = "bSelected"), BlueprintCosmetic)
		static UPARAM(DisplayName = "bClicked") bool Selectable(FString Label, UPARAM(ref) bool& bSelected, FVector2D Size);

	// ==== Widgets / List Boxes ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|ListBox", BlueprintCosmetic)
		static UPARAM(DisplayName = "bOpen") bool BeginListBox(FString Label, FVector2D Size);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|ListBox", BlueprintCosmetic)
		static void EndListBox();

	// Widgets: Data Plotting
	// Widgets: Value() Helpers.

	// ==== Widgets / Menus ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|Menu", BlueprintCosmetic)
		static UPARAM(DisplayName = "bOpen") bool BeginMenuBar();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|Menu", BlueprintCosmetic)
		static void EndMenuBar();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|Menu", BlueprintCosmetic)
		static UPARAM(DisplayName = "bOpen") bool BeginMainMenuBar();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|Menu", BlueprintCosmetic)
		static void EndMainMenuBar();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|Menu", BlueprintCosmetic)
		static UPARAM(DisplayName = "bOpen") bool BeginMenu(FString Label, bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|Menu", BlueprintCosmetic)
		static void EndMenu();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Widgets|Menu", BlueprintCosmetic)
		static UPARAM(DisplayName = "bActivated") bool MenuItem(FString Label, FString Shortcut, UPARAM(ref) bool& bSelected, bool bEnabled);

	// ==== Tooltips ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Tooltip", BlueprintCosmetic)
		static void BeginTooltip();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Tooltip", BlueprintCosmetic)
		static void EndTooltip();

	// ==== Popups / begin/end functions ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Popup", BlueprintCosmetic)
		static UPARAM(DisplayName = "bOpen") bool BeginPopup(FString HashName, UPARAM(meta = (Bitmask, BitmaskEnum = "/Script/ImGui.EImGuiWindowFlags")) int WindowFlagsBitmask);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Popup", meta = (AutoCreateRefTerm = "bOpenModal"), BlueprintCosmetic)
		static UPARAM(DisplayName = "bOpen") bool BeginPopupModal(FString Name, bool bClosable, UPARAM(ref) bool& bOpenModal, UPARAM(meta = (Bitmask, BitmaskEnum = "/Script/ImGui.EImGuiWindowFlags")) int WindowFlagsBitmask);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Popup", BlueprintCosmetic)
		static void EndPopup();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Popup", BlueprintCosmetic)
		static void OpenPopup(FString HashName);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Popup", BlueprintCosmetic)
		static void CloseCurrentPopup();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Popup", BlueprintPure, BlueprintCosmetic)
		static bool IsPopupOpen(FString HashName);

	// Popups: open/close functions
	// Popups: open+begin combined functions helpers
	// Popups: query functions

	// ==== Tables ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Table", BlueprintCosmetic)
		static UPARAM(DisplayName = "bOpen") bool BeginTable(FString HashName, int Column, FVector2D OuterSize, float InnerWidth);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Table", BlueprintCosmetic)
		static void EndTable();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Table", BlueprintCosmetic)
		static void TableNextRow(float MinRowHeight);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Table", BlueprintCosmetic)
		static UPARAM(DisplayName = "bVisible") bool TableNextColumn();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Table", BlueprintCosmetic)
		static UPARAM(DisplayName = "bVisible") bool TableSetColumnIndex(int Column);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Table", BlueprintCosmetic)
		static void TableHeader(FString Label);

	// Tables: Headers & Columns declaration
	// Tables: Sorting
	// Tables: Miscellaneous functions
	// Legacy Columns API (prefer using Tables!)
	// ==== Tab Bars / Tabs ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Tabs", BlueprintCosmetic)
		static UPARAM(DisplayName = "bVisible") bool BeginTabBar(FString HashName);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Tabs", BlueprintCosmetic)
		static void EndTabBar();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Tabs", meta = (AutoCreateRefTerm = "bOpen"), BlueprintCosmetic)
		static UPARAM(DisplayName = "bSelected") bool BeginTabItem(FString Label, bool bClosable, UPARAM(ref) bool& bOpen);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Tabs", BlueprintCosmetic)
		static void EndTabItem();

	UFUNCTION(BlueprintCallable, Category = "Imgui|Tabs", BlueprintCosmetic)
		static UPARAM(DisplayName = "bClicked") bool TabItemButton(FString Label);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Tabs", BlueprintCosmetic)
		static void SetNextTabItemClosed(FString Label);


	// Logging/Capture

	// ==== Drag and Drop ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|DragAndDrop", BlueprintCosmetic)
		static bool BeginDragDropSource();

	UFUNCTION(BlueprintCallable, Category = "Imgui|DragAndDrop", BlueprintCosmetic)
		static bool SetDragDropPayload(FString HashName);

	UFUNCTION(BlueprintCallable, Category = "Imgui|DragAndDrop", BlueprintCosmetic)
		static void EndDragDropSource();

	UFUNCTION(BlueprintCallable, Category = "Imgui|DragAndDrop", BlueprintCosmetic)
		static bool BeginDragDropTarget();

	UFUNCTION(BlueprintCallable, Category = "Imgui|DragAndDrop", BlueprintCosmetic)
		static bool AcceptDragDropPayload(FString HashName);

	UFUNCTION(BlueprintCallable, Category = "Imgui|DragAndDrop", BlueprintCosmetic)
		static void EndDragDropTarget();

	// ==== Disabling [BETA API] ====

	UFUNCTION(BlueprintCallable, Category = "Imgui|Disabling", BlueprintCosmetic)
		static void BeginDisabled(bool bDisabled = true);

	UFUNCTION(BlueprintCallable, Category = "Imgui|Disabling", BlueprintCosmetic)
		static void EndDisabled();

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

private:

	static ImVec2 GetScreenSizeInPixels(FVector2D ScreenSize = FVector2D(0, 0));

	static ImVec2 GetRelativeScreenPosition(FVector2D ScreenSize = FVector2D(0, 0));
};
