// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_VULKAN_VULKAN_WINDOW_H_
#define FLUTTER_VULKAN_VULKAN_WINDOW_H_

#include <utility>
#include <tuple>
#include <vector>

#include "lib/ftl/macros.h"
#include "vulkan_handle.h"
#include "vulkan_proc_table.h"
#include "vulkan_backbuffer.h"

namespace vulkan {

class VulkanWindow {
 public:
  VulkanWindow(void* native_window);

  ~VulkanWindow();

  bool IsValid() const;

 private:
  bool valid_;
  VulkanProcTable vk;
  VulkanHandle<VkInstance> instance_;
  VulkanHandle<VkSurfaceKHR> surface_;
  VulkanHandle<VkPhysicalDevice> physical_device_;
  VulkanHandle<VkDevice> device_;
  VulkanHandle<VkQueue> queue_;
  VulkanHandle<VkSwapchainKHR> swapchain_;
  std::vector<std::unique_ptr<VulkanBackbuffer>> backbuffers_;
  VulkanHandle<VkCommandPool> command_pool_;

  bool CreateInstance();

  bool CreateSurface(void* native_window);

  bool SelectPhysicalDevice();

  bool CreateLogicalDevice();

  bool AcquireDeviceQueue();

  bool CreateSwapChain();

  bool SetupBuffers();

  bool CreateCommandPool();

  std::pair<bool, VkSurfaceFormatKHR> ChooseSurfaceFormat();

  std::pair<bool, VkPresentModeKHR> ChoosePresentMode();

  FTL_DISALLOW_COPY_AND_ASSIGN(VulkanWindow);
};

}  // namespace vulkan

#endif  // FLUTTER_VULKAN_VULKAN_WINDOW_H_
