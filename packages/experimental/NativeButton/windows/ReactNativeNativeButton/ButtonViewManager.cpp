#include "pch.h"
#include "ButtonViewManager.h"
#include "NativeModules.h"
#include "ButtonView.h"

namespace winrt {
    using namespace Microsoft::ReactNative;
    using namespace Windows::Foundation::Collections;

    namespace xaml = winrt::Windows::UI::Xaml;
}

namespace winrt::ReactNativeNativeButton::implementation {

    ButtonViewManager::ButtonViewManager() {}

    // IViewManager
    winrt::hstring ButtonViewManager::Name() noexcept {
        return L"MSFButtonView";
    }

    xaml::FrameworkElement ButtonViewManager::CreateView() noexcept {
        return winrt::ReactNativeNativeButton::ButtonView(m_reactContext);
    }

    // IViewManagerWithReactContext
    winrt::IReactContext ButtonViewManager::ReactContext() noexcept {
        return m_reactContext;
    }

    void ButtonViewManager::ReactContext(IReactContext reactContext) noexcept {
        m_reactContext = reactContext;
    }

    // IViewManagerWithNativeProperties
    IMapView<hstring, ViewManagerPropertyType> ButtonViewManager::NativeProps() noexcept {
        auto nativeProps = winrt::single_threaded_map<hstring, ViewManagerPropertyType>();

        nativeProps.Insert(L"title", ViewManagerPropertyType::String);
        nativeProps.Insert(L"image", ViewManagerPropertyType::Map);
        nativeProps.Insert(L"accentColor", ViewManagerPropertyType::Color);
        nativeProps.Insert(L"buttonStyle", ViewManagerPropertyType::String);
        nativeProps.Insert(L"enabled", ViewManagerPropertyType::Boolean);
        nativeProps.Insert(L"toolTip", ViewManagerPropertyType::String);

        return nativeProps.GetView();
    }

    void ButtonViewManager::UpdateProperties(xaml::FrameworkElement const& view,
        IJSValueReader const& propertyMapReader) noexcept {
        if (auto buttonView = view.try_as<ButtonView>()) {
            buttonView->UpdateProperties(propertyMapReader);
        } else {
            OutputDebugStringW(L"Type deduction for ButtonView failed.");
        }
    }

    // IViewManagerWithExportedEventTypeConstants
    ConstantProviderDelegate ButtonViewManager::ExportedCustomBubblingEventTypeConstants() noexcept {
        return nullptr;
    }

    ConstantProviderDelegate ButtonViewManager::ExportedCustomDirectEventTypeConstants() noexcept {
        return [](winrt::IJSValueWriter const& constantWriter) {
            WriteCustomDirectEventTypeConstant(constantWriter, "onChange");
            WriteCustomDirectEventTypeConstant(constantWriter, L"topPress");
        };
    }

}