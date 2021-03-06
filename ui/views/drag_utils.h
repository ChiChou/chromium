// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_DRAG_UTILS_H_
#define UI_VIEWS_DRAG_UTILS_H_
#pragma once

#include "ui/gfx/native_widget_types.h"
#include "ui/views/views_export.h"

namespace gfx {
class Point;
}

namespace ui {
class OSExchangeData;
}

namespace views {

// Starts a drag operation. This blocks until the drag operation completes.
VIEWS_EXPORT void RunShellDrag(gfx::NativeView view,
                            const ui::OSExchangeData& data,
                            const gfx::Point& location,
                            int operation);

}  // namespace views

#endif  // UI_VIEWS_DRAG_UTILS_H_
