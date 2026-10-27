/*
 * Copyright (C) 2015 Canonical Ltd.
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

#include "mock_application_info.h"
#include "mock_task_controller.h"

namespace qtmir
{

MockTaskController::MockTaskController(std::shared_ptr<qtmir::PromptSessionManager> promptSessionManager, QObject *parent)
    : TaskController(promptSessionManager, parent)
{
    using namespace ::testing;

    ON_CALL(*this, getInfoForApp(_))
            .WillByDefault(
                Invoke(this, &MockTaskController::doGetInfoForApp));

    ON_CALL(*this, start(_, _))
            .WillByDefault(Return(true));
}

MockTaskController::~MockTaskController()
{

}

QSharedPointer<qtmir::ApplicationInfo> MockTaskController::doGetInfoForApp(const QString& appId) const
{
    return QSharedPointer<qtmir::ApplicationInfo>(new testing::NiceMock<MockApplicationInfo>(appId));
}

} // namespace qtmir
