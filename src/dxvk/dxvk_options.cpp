#include "dxvk_options.h"

namespace dxvk {

  DxvkOptions::DxvkOptions(const Config& config) {
    enableDebugUtils      = config.getOption<bool>    ("dxvk.enableDebugUtils",       false);
    enableStateCache      = config.getOption<bool>    ("dxvk.enableStateCache",       true);
    numCompilerThreads    = config.getOption<int32_t> ("dxvk.numCompilerThreads",     0);
    enableGraphicsPipelineLibrary = config.getOption<Tristate>("dxvk.enableGraphicsPipelineLibrary", Tristate::Auto);
    useRawSsbo            = config.getOption<Tristate>("dxvk.useRawSsbo",             Tristate::Auto);
    shrinkNvidiaHvvHeap   = config.getOption<bool>    ("dxvk.shrinkNvidiaHvvHeap",    false);
    hud                   = config.getOption<std::string>("dxvk.hud", "");
  }

}
