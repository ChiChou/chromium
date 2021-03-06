// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_MAC_CFBUNDLE_BLOCKER_H_
#define CHROME_COMMON_MAC_CFBUNDLE_BLOCKER_H_
#pragma once

#if defined(__OBJC__)
@class NSString;
#else
class NSString;
#endif

namespace chrome {
namespace common {
namespace mac {

// Arranges to block loading of some third-party plug-in code that might try
// to inject itself into the process. Modules loaded by CFBundle are blocked
// if located within specific directories. Because NSBundle uses CFBundle
// behind the scenes, this also blocks modules loaded by NSBundle when located
// in those same specific directories.
//
// Blocked modules include input managers, contextual menu items, and
// scripting additions installed in per-user (~/Library), per-machine
// (/Library), or network (/Network/Library) locations. Modules installed in
// the operating system location (/System/Library) are never blocked.
//
// This mechanism does not prevent CFBundle (or NSBundle) objects from being
// created, but it does block them from loading modules into the process.
void EnableCFBundleBlocker();

// Returns true if |bundle_id| and |version| identify a bundle that is allowed
// to be loaded even when found in a blocked directory.
//
// Exposed only for testing. Do not call from outside the implementation.
bool IsBundleAllowed(NSString* bundle_id, NSString* version);

}  // namespace mac
}  // namespace common
}  // namespace chrome

#endif  // CHROME_COMMON_MAC_CFBUNDLE_BLOCKER_H_
