#include "pch.h"
#include "JSValueXaml.h"
#include "ButtonView.h"
#include "ButtonView.g.cpp"

#include <limits>
#include <stdexcept>

#include "winrt/Windows.UI.Xaml.Media.Imaging.h"

namespace winrt {
    using namespace Microsoft::ReactNative;
    using namespace Windows::Foundation;
    using namespace Windows::UI::Xaml::Media;
    using namespace Windows::UI::Xaml::Media::Imaging;
    using namespace Windows::UI::Xaml::Controls;
}

namespace winrt::ReactNativeNativeButton::implementation {

    ButtonView::ButtonView(winrt::IReactContext const& reactContext) : m_reactContext(reactContext) {
        RegisterEvents();
    }

    void ButtonView::RegisterEvents() {
        m_buttonClickRevoker = this->Click(winrt::auto_revoke,
            [ref = get_weak()](auto const& sender, auto const& args) {
            if (auto self = ref.get()) {
                self->OnPress(sender, args);
            }
        });
    }

    void ButtonView::UpdateProperties(winrt::IJSValueReader const& reader) {
        m_updating = true;

        auto const& propertyMap = JSValueObject::ReadFrom(reader);

        for (auto const& pair : propertyMap) {
            auto const& propertyName = pair.first;
            auto const& propertyValue = pair.second;

            if (propertyName == "title") {
                if (!propertyValue.IsNull()) {
                    this->Content(winrt::box_value(to_hstring(propertyValue.AsString())));
                }
                else {
                    this->Content(winrt::box_value(L""));
                }
            }
            else if (propertyName == "image") {
                if (!propertyValue.IsNull()) {

                    auto imgUriString = propertyValue.AsObject()["uri"].AsString();
                    BitmapImage bitmap = BitmapImage(Uri(to_hstring(imgUriString)));
                    Image imgB = Image();
                    imgB.Source(bitmap);
                    this->Content(imgB);

                }
            }
            else if (propertyName == "buttonStyle") {
                if (!propertyValue.IsNull()) {
                    auto style = propertyValue.AsString();
                    auto resDict = this->Resources();

                    if (style == "primary") {
                        resDict.Insert(winrt::box_value(L"ButtonForeground"), m_neutralInverted);
                        resDict.Insert(winrt::box_value(L"ButtonForegroundPressed"), m_neutralInverted);
                        resDict.Insert(winrt::box_value(L"ButtonForegroundDisabled"), m_brandForegroundDisabled);
                        resDict.Insert(winrt::box_value(L"ButtonBackground"), m_accentColor);
                        resDict.Insert(winrt::box_value(L"ButtonBackgroundPressed"), m_accentColor);
                        resDict.Insert(winrt::box_value(L"ButtonBackgroundDisabled"), m_brandBackgroundDisabled);
                        resDict.Insert(winrt::box_value(L"ButtonBorderBrush"), m_transparentBrush);
                        resDict.Insert(winrt::box_value(L"ButtonBorderBrushPressed"), m_transparentBrush);
                        resDict.Insert(winrt::box_value(L"ButtonBorderBrushDisabled"), m_transparentBrush);
                    }
                    else if (style == "secondary") {
                        resDict.Insert(winrt::box_value(L"ButtonForegroundPressed"), m_neutralInverted);
                        resDict.Insert(winrt::box_value(L"ButtonBackground"), m_neutralBackground2);
                        resDict.Insert(winrt::box_value(L"ButtonBackgroundPressed"), m_accentColor);
                        resDict.Insert(winrt::box_value(L"ButtonBackgroundDisabled"), m_neutralBackground2);
                        resDict.Insert(winrt::box_value(L"ButtonBorderBrush"), m_neutralStroke2);
                        resDict.Insert(winrt::box_value(L"ButtonBorderBrushPressed"), m_transparentBrush);
                        resDict.Insert(winrt::box_value(L"ButtonBorderBrushDisabled"), m_neutralStroke2);
                    }
                    else if (style == "borderless") {
                        resDict.Insert(winrt::box_value(L"ButtonForeground"), m_accentColor);
                        resDict.Insert(winrt::box_value(L"ButtonForegroundPointerOver"), m_accentColor);
                        resDict.Insert(winrt::box_value(L"ButtonForegroundPressed"), m_accentColor);
                        resDict.Insert(winrt::box_value(L"ButtonForegroundDisabled"), m_brandForegroundDisabled);
                        resDict.Insert(winrt::box_value(L"ButtonBackground"), m_transparentBrush);
                        resDict.Insert(winrt::box_value(L"ButtonBackgroundPointerOver"), m_transparentBrush);
                        resDict.Insert(winrt::box_value(L"ButtonBackgroundPressed"), m_transparentBrush);
                        resDict.Insert(winrt::box_value(L"ButtonBackgroundDisabled"), m_transparentBrush);
                        resDict.Insert(winrt::box_value(L"ButtonBorderBrush"), m_transparentBrush);
                        resDict.Insert(winrt::box_value(L"ButtonBorderBrushPointerOver"), m_transparentBrush);
                        resDict.Insert(winrt::box_value(L"ButtonBorderBrushPressed"), m_transparentBrush);
                        resDict.Insert(winrt::box_value(L"ButtonBorderBrushDisabled"), m_transparentBrush);
                    }
                }
            }
            else if (propertyName == "enabled") {
                if (!propertyValue.IsNull()) {
                    this->IsEnabled(propertyValue.AsBoolean());
                }
                else {
                    this->IsEnabled(true);
                }
            }
            else if (propertyName == "toolTip") {
                if (!propertyValue.IsNull()) {

                    auto self = this->try_as<xaml::Controls::Button>();

                    ToolTip toolTip = ToolTip();
                    toolTip.Content(winrt::box_value(to_hstring(propertyValue.AsString())));
                    ToolTipService::SetToolTip(self, toolTip);
                }
            }
            else if (propertyName == "accentColor") {
                if (!propertyValue.IsNull()) {
                    m_accentColor = propertyValue.To<winrt::Brush>();
                }
            }
        }


        m_updating = false;
    }

    void ButtonView::OnPress(winrt::IInspectable const& sender, xaml::RoutedEventArgs const& args){
        if (!m_updating) {

            m_reactContext.DispatchEvent(
                *this,
                L"topPress",
                [&](winrt::Microsoft::ReactNative::IJSValueWriter const& eventDataWriter) noexcept {});
        }
    }

}