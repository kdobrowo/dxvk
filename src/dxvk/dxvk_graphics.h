#pragma once

#include <mutex>

#include "../util/sync/sync_list.h"

#include "dxvk_bind_mask.h"
#include "dxvk_constant_state.h"
#include "dxvk_graphics_state.h"
#include "dxvk_pipelayout.h"
#include "dxvk_renderpass.h"
#include "dxvk_resource.h"
#include "dxvk_shader.h"
#include "dxvk_stats.h"

namespace dxvk {
  
  class DxvkDevice;
  class DxvkStateCache;
  class DxvkPipelineManager;
  class DxvkPipelineWorkers;
  struct DxvkPipelineStats;

  /**
   * \brief Vertex input info for graphics pipelines
   *
   * Can be used to compile dedicated pipeline objects for use
   * in a graphics pipeline library, or as part of the data
   * required to compile a full graphics pipeline.
   */
  struct DxvkGraphicsPipelineVertexInputState {
    DxvkGraphicsPipelineVertexInputState();

    DxvkGraphicsPipelineVertexInputState(
      const DxvkDevice*                     device,
      const DxvkGraphicsPipelineStateInfo&  state,
      const DxvkShader*                     vs);

    VkPipelineInputAssemblyStateCreateInfo          iaInfo        = { VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };
    VkPipelineVertexInputStateCreateInfo            viInfo        = { VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };
    VkPipelineVertexInputDivisorStateCreateInfoEXT  viDivisorInfo = { VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_EXT };

    std::array<VkVertexInputBindingDescription,           MaxNumVertexBindings>   viBindings    = { };
    std::array<VkVertexInputBindingDivisorDescriptionEXT, MaxNumVertexBindings>   viDivisors    = { };
    std::array<VkVertexInputAttributeDescription,         MaxNumVertexAttributes> viAttributes  = { };

    VkBool32 viUseDynamicVertexStrides = VK_FALSE;

    bool eq(const DxvkGraphicsPipelineVertexInputState& other) const;

    size_t hash() const;
  };


  /**
   * \brief Vertex input pipeline library
   *
   * Creates a Vulkan pipeline object for a
   * given vertex input state vector.
   */
  class DxvkGraphicsPipelineVertexInputLibrary {

  public:

    DxvkGraphicsPipelineVertexInputLibrary(
            DxvkDevice*                           device,
      const DxvkGraphicsPipelineVertexInputState& state);

    ~DxvkGraphicsPipelineVertexInputLibrary();

    VkPipeline getHandle() const {
      return m_pipeline;
    }

  private:

    DxvkDevice* m_device;
    VkPipeline  m_pipeline;

  };


  /**
   * \brief Fragment output info for graphics pipelines
   *
   * Can be used to compile dedicated pipeline objects for use
   * in a graphics pipeline library, or as part of the data
   * required to compile a full graphics pipeline.
   */
  struct DxvkGraphicsPipelineFragmentOutputState {
    DxvkGraphicsPipelineFragmentOutputState();

    DxvkGraphicsPipelineFragmentOutputState(
      const DxvkDevice*                     device,
      const DxvkGraphicsPipelineStateInfo&  state,
      const DxvkShader*                     fs);

    VkPipelineRenderingCreateInfo                   rtInfo = { VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO };
    VkPipelineColorBlendStateCreateInfo             cbInfo = { VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO };
    VkPipelineMultisampleStateCreateInfo            msInfo = { VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };

    uint32_t                                        msSampleMask               = 0u;
    VkBool32                                        cbUseDynamicBlendConstants = VK_FALSE;

    std::array<VkPipelineColorBlendAttachmentState, MaxNumRenderTargets> cbAttachments  = { };
    std::array<VkFormat,                            MaxNumRenderTargets> rtColorFormats = { };

    bool eq(const DxvkGraphicsPipelineFragmentOutputState& other) const;

    size_t hash() const;
  };


  /**
   * \brief Vertex input pipeline library
   *
   * Creates a Vulkan pipeline object for a
   * given vertex input state vector.
   */
  class DxvkGraphicsPipelineFragmentOutputLibrary {

  public:

    DxvkGraphicsPipelineFragmentOutputLibrary(
            DxvkDevice*                               device,
      const DxvkGraphicsPipelineFragmentOutputState&  state);

    ~DxvkGraphicsPipelineFragmentOutputLibrary();

    VkPipeline getHandle() const {
      return m_pipeline;
    }

  private:

    DxvkDevice* m_device;
    VkPipeline  m_pipeline;

  };


  /**
   * \brief Pre-rasterization info for graphics pipelines
   *
   * Can only be used when compiling full graphics pipelines
   * when all pipeline state is known.
   */
  struct DxvkGraphicsPipelinePreRasterizationState {
    DxvkGraphicsPipelinePreRasterizationState();

    DxvkGraphicsPipelinePreRasterizationState(
      const DxvkDevice*                     device,
      const DxvkGraphicsPipelineStateInfo&  state,
      const DxvkShader*                     gs);

    VkPipelineViewportStateCreateInfo                     vpInfo              = { VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };
    VkPipelineTessellationStateCreateInfo                 tsInfo              = { VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO };
    VkPipelineRasterizationStateCreateInfo                rsInfo              = { VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO };
    VkPipelineRasterizationDepthClipStateCreateInfoEXT    rsDepthClipInfo     = { VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_DEPTH_CLIP_STATE_CREATE_INFO_EXT };
    VkPipelineRasterizationStateStreamCreateInfoEXT       rsXfbStreamInfo     = { VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_STREAM_CREATE_INFO_EXT };
    VkPipelineRasterizationConservativeStateCreateInfoEXT rsConservativeInfo  = { VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_CONSERVATIVE_STATE_CREATE_INFO_EXT };
  };


  /**
   * \brief Fragment shader state info for graphics pipelines
   *
   * Can only be used when compiling full graphics pipelines
   * when all pipeline state is known.
   */
  struct DxvkGraphicsPipelineFragmentShaderState {
    DxvkGraphicsPipelineFragmentShaderState();

    DxvkGraphicsPipelineFragmentShaderState(
      const DxvkDevice*                     device,
      const DxvkGraphicsPipelineStateInfo&  state);

    VkPipelineDepthStencilStateCreateInfo           dsInfo = { VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO };
  };

  
  /**
   * \brief Flags that describe pipeline properties
   */
  enum class DxvkGraphicsPipelineFlag {
    HasRasterizerDiscard,
    HasTransformFeedback,
    HasStorageDescriptors,
  };

  using DxvkGraphicsPipelineFlags = Flags<DxvkGraphicsPipelineFlag>;


  /**
   * \brief Shaders used in graphics pipelines
   */
  struct DxvkGraphicsPipelineShaders {
    Rc<DxvkShader> vs;
    Rc<DxvkShader> tcs;
    Rc<DxvkShader> tes;
    Rc<DxvkShader> gs;
    Rc<DxvkShader> fs;

    bool eq(const DxvkGraphicsPipelineShaders& other) const {
      return vs == other.vs && tcs == other.tcs
          && tes == other.tes && gs == other.gs
          && fs == other.fs;
    }

    size_t hash() const {
      DxvkHashState state;
      state.add(DxvkShader::getHash(vs));
      state.add(DxvkShader::getHash(tcs));
      state.add(DxvkShader::getHash(tes));
      state.add(DxvkShader::getHash(gs));
      state.add(DxvkShader::getHash(fs));
      return state;
    }

    bool validate() const {
      return validateShaderType(vs, VK_SHADER_STAGE_VERTEX_BIT)
          && validateShaderType(tcs, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT)
          && validateShaderType(tes, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT)
          && validateShaderType(gs, VK_SHADER_STAGE_GEOMETRY_BIT)
          && validateShaderType(fs, VK_SHADER_STAGE_FRAGMENT_BIT);
    }

    static bool validateShaderType(const Rc<DxvkShader>& shader, VkShaderStageFlagBits stage) {
      return shader == nullptr || shader->info().stage == stage;
    }
  };


  /**
   * \brief Graphics pipeline type
   */
  enum class DxvkGraphicsPipelineType : uint32_t {
    BasePipeline = 0, ///< Unoptimized pipeline using graphics pipeline libraries
    FastPipeline = 1, ///< Monolithic pipeline with less dynamic state
  };


  /**
   * \brief Graphics pipeline instance
   * 
   * Stores a state vector and the
   * corresponding pipeline handle.
   */
  struct DxvkGraphicsPipelineInstance {
    DxvkGraphicsPipelineInstance() { }
    DxvkGraphicsPipelineInstance(
      const DxvkGraphicsPipelineStateInfo&  state_,
            VkPipeline                      baseHandle_,
            VkPipeline                      fastHandle_)
    : state       (state_),
      baseHandle  (baseHandle_),
      fastHandle  (fastHandle_),
      isCompiling (fastHandle_ != VK_NULL_HANDLE) { }

    DxvkGraphicsPipelineStateInfo state;
    std::atomic<VkPipeline>       baseHandle  = { VK_NULL_HANDLE };
    std::atomic<VkPipeline>       fastHandle  = { VK_NULL_HANDLE };
    std::atomic<VkBool32>         isCompiling = { VK_FALSE };
  };


  /**
   * \brief Base instance key
   *
   * Stores the libraries and arguments used to
   * compile a base pipeline.
   */
  struct DxvkGraphicsPipelineBaseInstanceKey {
    const DxvkGraphicsPipelineVertexInputLibrary*     viLibrary = nullptr;
    const DxvkGraphicsPipelineFragmentOutputLibrary*  foLibrary = nullptr;
    DxvkShaderPipelineLibraryCompileArgs              args;
  };


  /**
   * \brief Base pipeline instance
   *
   * Stores the key and handle of a base pipeline.
   */
  struct DxvkGraphicsPipelineBaseInstance {
    DxvkGraphicsPipelineBaseInstance() { }
    DxvkGraphicsPipelineBaseInstance(
      const DxvkGraphicsPipelineBaseInstanceKey&  key_,
            VkPipeline                            handle_)
    : key(key_), handle(handle_) { }

    DxvkGraphicsPipelineBaseInstanceKey key;
    VkPipeline                          handle = VK_NULL_HANDLE;
  };

  
  /**
   * \brief Graphics pipeline
   * 
   * Stores the pipeline layout as well as methods to
   * recompile the graphics pipeline against a given
   * pipeline state vector.
   */
  class DxvkGraphicsPipeline {
    
  public:
    
    DxvkGraphicsPipeline(
            DxvkDevice*                 device,
            DxvkPipelineManager*        pipeMgr,
            DxvkGraphicsPipelineShaders shaders,
            DxvkBindingLayoutObjects*   layout,
            DxvkShaderPipelineLibrary*  vsLibrary,
            DxvkShaderPipelineLibrary*  fsLibrary);

    ~DxvkGraphicsPipeline();

    /**
     * \brief Shaders used by the pipeline
     * \returns Shaders used by the pipeline
     */
    const DxvkGraphicsPipelineShaders& shaders() const {
      return m_shaders;
    }
    
    /**
     * \brief Returns graphics pipeline flags
     * \returns Graphics pipeline property flags
     */
    DxvkGraphicsPipelineFlags flags() const {
      return m_flags;
    }
    
    /**
     * \brief Pipeline layout
     * 
     * Stores the pipeline layout and the descriptor set
     * layout, as well as information on the resource
     * slots used by the pipeline.
     * \returns Pipeline layout
     */
    DxvkBindingLayoutObjects* getBindings() const {
      return m_bindings;
    }

    /**
     * \brief Queries global resource barrier
     *
     * Returns the stages that can access resources in this
     * pipeline with the given pipeline state, as well as
     * the ways in which resources are accessed. This does
     * not include render targets. The barrier is meant to
     * be executed after the render pass.
     * \returns Global barrier
     */
    DxvkGlobalPipelineBarrier getGlobalBarrier(
      const DxvkGraphicsPipelineStateInfo&    state) const;

    /**
     * \brief Pipeline handle
     * 
     * Retrieves a pipeline handle for the given pipeline
     * state. If necessary, a new pipeline will be created.
     * \param [in] state Pipeline state vector
     * \returns Pipeline handle and handle type
     */
    std::pair<VkPipeline, DxvkGraphicsPipelineType> getPipelineHandle(
      const DxvkGraphicsPipelineStateInfo&    state);
    
    /**
     * \brief Compiles a pipeline
     * 
     * Asynchronously compiles the given pipeline
     * and stores the result for future use.
     * \param [in] state Pipeline state vector
     */
    void compilePipeline(
      const DxvkGraphicsPipelineStateInfo&    state);
    
  private:

    DxvkDevice*                 m_device;    
    DxvkPipelineManager*        m_manager;
    DxvkPipelineWorkers*        m_workers;
    DxvkStateCache*             m_stateCache;
    DxvkPipelineStats*          m_stats;

    DxvkGraphicsPipelineShaders m_shaders;
    DxvkBindingLayoutObjects*   m_bindings;
    DxvkGlobalPipelineBarrier   m_barrier;
    DxvkGraphicsPipelineFlags   m_flags;

    DxvkShaderPipelineLibrary*  m_vsLibrary;
    DxvkShaderPipelineLibrary*  m_fsLibrary;

    uint32_t m_vsIn  = 0;
    uint32_t m_fsOut = 0;
    
    // List of pipeline instances, shared between threads
    alignas(CACHE_LINE_SIZE)
    dxvk::mutex                                   m_mutex;
    sync::List<DxvkGraphicsPipelineInstance>      m_pipelines;
    sync::List<DxvkGraphicsPipelineBaseInstance>  m_basePipelines;
    
    DxvkGraphicsPipelineInstance* createInstance(
      const DxvkGraphicsPipelineStateInfo& state,
            bool                           doCreateBasePipeline);
    
    DxvkGraphicsPipelineInstance* findInstance(
      const DxvkGraphicsPipelineStateInfo& state);

    DxvkGraphicsPipelineBaseInstance* createBaseInstance(
      const DxvkGraphicsPipelineBaseInstanceKey& key);

    bool canCreateBasePipeline(
      const DxvkGraphicsPipelineStateInfo& state) const;

    VkPipeline createBasePipeline(
      const DxvkGraphicsPipelineBaseInstanceKey& key) const;
    
    VkPipeline createOptimizedPipeline(
      const DxvkGraphicsPipelineStateInfo& state,
            VkPipelineCreateFlags          flags) const;
    
    void destroyPipeline(
            VkPipeline                     pipeline) const;
    
    SpirvCodeBuffer getShaderCode(
      const Rc<DxvkShader>&                shader,
      const DxvkGraphicsPipelineStateInfo& state) const;
    
    Rc<DxvkShader> getPrevStageShader(
            VkShaderStageFlagBits          stage) const;

    bool writesRenderTarget(
      const DxvkGraphicsPipelineStateInfo& state,
            uint32_t                       target) const;

    bool validatePipelineState(
      const DxvkGraphicsPipelineStateInfo& state,
            bool                           trusted) const;
    
    void writePipelineStateToCache(
      const DxvkGraphicsPipelineStateInfo& state) const;
    
    void logPipelineState(
            LogLevel                       level,
      const DxvkGraphicsPipelineStateInfo& state) const;

  };
  
}