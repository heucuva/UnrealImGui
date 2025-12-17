// Distributed under the MIT License (MIT) (see accompanying LICENSE file)

#pragma once

#include "Styling/SlateTypes.h"
#include "InputCoreTypes.h"
#include "Input/Events.h"

#include "ImGuiKeyInfo.generated.h"

/**
 * Struct containing key information that can be used for key binding. Using 'Undetermined' value for modifier keys
 * means that those keys should be ignored when testing for a match.
 */
USTRUCT()
struct IMGUI_API FImGuiKeyInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Input")
	FKey Key;

	UPROPERTY(EditAnywhere, Category = "Input")
	ECheckBoxState Shift = ECheckBoxState::Undetermined;

	UPROPERTY(EditAnywhere, Category = "Input")
	ECheckBoxState Ctrl = ECheckBoxState::Undetermined;

	UPROPERTY(EditAnywhere, Category = "Input")
	ECheckBoxState Alt = ECheckBoxState::Undetermined;

	UPROPERTY(EditAnywhere, Category = "Input")
	ECheckBoxState Cmd = ECheckBoxState::Undetermined;

	friend bool operator==(const FImGuiKeyInfo& Lhs, const FImGuiKeyInfo& Rhs)
	{
		return Lhs.Key == Rhs.Key
			&& Lhs.Shift == Rhs.Shift
			&& Lhs.Ctrl == Rhs.Ctrl
			&& Lhs.Alt == Rhs.Alt
			&& Lhs.Cmd == Rhs.Cmd;
	}

	friend bool operator!=(const FImGuiKeyInfo& Lhs, const FImGuiKeyInfo& Rhs)
	{
		return !(Lhs == Rhs);
	}

	static bool IsMatching(ECheckBoxState CheckBoxState, bool bValue)
	{
		return (CheckBoxState == ECheckBoxState::Undetermined) || ((CheckBoxState == ECheckBoxState::Checked) == bValue);
	}

	static bool IsMatchingEvent(const FKeyEvent& KeyEvent, const FImGuiKeyInfo& KeyInfo)
	{
		return (KeyInfo.Key == KeyEvent.GetKey())
			&& IsMatching(KeyInfo.Shift, KeyEvent.IsShiftDown())
			&& IsMatching(KeyInfo.Ctrl, KeyEvent.IsControlDown())
			&& IsMatching(KeyInfo.Alt, KeyEvent.IsAltDown())
			&& IsMatching(KeyInfo.Cmd, KeyEvent.IsCommandDown());
	}

	bool MatchesEvent(const FKeyEvent& KeyEvent) const
	{
		return IsMatchingEvent(KeyEvent, *this);
	}

	static void UpdatePlayerInputs(const FImGuiKeyInfo& KeyInfo, const FString& CommandToBindTo);
};
