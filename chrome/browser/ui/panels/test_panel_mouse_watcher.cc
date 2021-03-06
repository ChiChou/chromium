// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/panels/test_panel_mouse_watcher.h"

#include "testing/gtest/include/gtest/gtest.h"

TestPanelMouseWatcher::TestPanelMouseWatcher()
    : started_(false) {
}

TestPanelMouseWatcher::~TestPanelMouseWatcher() {
  EXPECT_FALSE(IsActive());
}

void TestPanelMouseWatcher::Start() {
  EXPECT_FALSE(IsActive());
  started_ = true;
}

void TestPanelMouseWatcher::Stop() {
  EXPECT_TRUE(IsActive());
  started_ = false;
}

bool TestPanelMouseWatcher::IsActive() const {
  return started_;
}
