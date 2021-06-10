#include "pch.h"
#include "ReactPackageProvider.h"
#if __has_include("ReactPackageProvider.g.cpp")
#include "ReactPackageProvider.g.cpp"
#endif

//#include "ReactNativeModule.h"

#include "ButtonViewManager.h"

using namespace winrt::Microsoft::ReactNative;

namespace winrt::ReactNativeNativeButton::implementation
{

void ReactPackageProvider::CreatePackage(IReactPackageBuilder const &packageBuilder) noexcept
{
    //AddAttributedModules(packageBuilder);
    packageBuilder.AddViewManager(L"ButtonViewManager", []() { return winrt::make<ButtonViewManager>(); });
}

} // namespace winrt::ReactNativeNativeButton::implementation
