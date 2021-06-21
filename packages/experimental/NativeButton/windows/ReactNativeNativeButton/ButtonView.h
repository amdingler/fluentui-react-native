#pragma once

#include "ButtonView.g.h"
#include "winrt/Microsoft.ReactNative.h"
#include "NativeModules.h"

namespace winrt::ReactNativeNativeButton::implementation {

    namespace xaml = winrt::Windows::UI::Xaml;

    class ButtonView : public ButtonViewT<ButtonView> {
    public:
        ButtonView(Microsoft::ReactNative::IReactContext const& reactContext);
        void UpdateProperties(Microsoft::ReactNative::IJSValueReader const& reader);

    private:
        Microsoft::ReactNative::IReactContext m_reactContext{ nullptr };
        bool m_updating{ false };
        xaml::Controls::Button::Click_revoker m_buttonClickRevoker{};
        void RegisterEvents();
        void OnPress(winrt::Windows::Foundation::IInspectable const& sender, xaml::RoutedEventArgs const& args);

        xaml::Media::Brush m_accentColor{ nullptr };
        xaml::Media::SolidColorBrush m_transparentBrush{ winrt::Windows::UI::Colors::Transparent() };
        xaml::Media::SolidColorBrush m_neutralInverted{ winrt::Windows::UI::ColorHelper::FromArgb(255,255,255,255) };
        xaml::Media::SolidColorBrush m_brandForegroundDisabled{ winrt::Windows::UI::ColorHelper::FromArgb(64,37,37,37) };
        xaml::Media::SolidColorBrush m_brandBackgroundDisabled{ winrt::Windows::UI::ColorHelper::FromArgb(64,37,37,37) };
        xaml::Media::SolidColorBrush m_neutralBackground2{ winrt::Windows::UI::ColorHelper::FromArgb(255,255,255,255) };
        xaml::Media::SolidColorBrush m_neutralStroke2{ winrt::Windows::UI::ColorHelper::FromArgb(38,0,0,0) };
        xaml::Media::SolidColorBrush m_neutralForeground3{ winrt::Windows::UI::ColorHelper::FromArgb(255,39,39,39) };
        xaml::Media::SolidColorBrush m_neutralBackground3{ winrt::Windows::UI::ColorHelper::FromArgb(13,0,0,0) };

    };
}

namespace winrt::ReactNativeNativeButton::factory_implementation {
    struct ButtonView : ButtonViewT<ButtonView, implementation::ButtonView> {};
}