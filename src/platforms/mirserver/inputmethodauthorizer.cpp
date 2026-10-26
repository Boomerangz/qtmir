/*
 * Copyright (C) 2026 UBports Foundation
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3, as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranties of MERCHANTABILITY,
 * SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "inputmethodauthorizer.h"

#include <QFileInfo>
#include <QString>

bool qtmir::isTrustedInputMethod(pid_t pid)
{
    // TODO: brute-force check on the binary path, wp_security_context_v1 would be the proper way
    const QString binaryPath = QFileInfo(QStringLiteral("/proc/%1/exe").arg(pid)).symLinkTarget();
    return binaryPath == QLatin1String("/usr/bin/maliit-server")
        || binaryPath == QLatin1String("/usr/bin/maliit6-server");
}
