// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

// --- Handedness ---
// Use EE_HANDS — it's the most flexible and lets you plug USB into either half.
// Flash each half with eeprom-lefthand.bin / eeprom-righthand.bin once.
#define EE_HANDS

// --- Master detection (USB activity-based, since Blok has no VBUS sense) ---
// Already implicit on ChibiOS/ARM, but be explicit for clarity:
#define SPLIT_USB_DETECT

// Increase the timeout — default is 1000ms, but cold-boot host enumeration
// can be slow. 2000-3000ms gives the host time to start enumerating before
// the master detection gives up.
#define SPLIT_USB_TIMEOUT 2000

// Polling interval during master detection. Default 10ms. Lower = faster
// detection once host appears.
#define SPLIT_USB_TIMEOUT_POLL 10

// --- Slave watchdog ---
// Reboots the slave half if it doesn't hear from the master within the
// timeout. Helps recover from the "both halves think they're slave" race.
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_WATCHDOG_TIMEOUT 3000

// --- Communication safety net ---
// Forces a sync from master to slave at this interval even with no changes.
// Default is 100ms, which is fine.
#define SPLIT_MAX_MATRIX_SYNC_INTERVAL 100

// --- USB suspend behavior (helps with KVMs and hubs) ---
// Don't wait for the host to wake the keyboard before scanning.
#define NO_USB_STARTUP_CHECK
