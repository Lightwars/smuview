/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2018-2021 Frank Stettner <frank-stettner@gmx.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UI_DIALOGS_SELECTSIGNALDIALOG_HPP
#define UI_DIALOGS_SELECTSIGNALDIALOG_HPP

#include <memory>
#include <vector>

#include <QDialog>
#include <QDialogButtonBox>

#include "src/session.hpp"

using std::shared_ptr;
using std::vector;

namespace sv {

namespace data {
class BaseSignal;
}
namespace devices {
class BaseDevice;
}

namespace ui {

namespace devices {
namespace devicetree {
class DeviceTreeView;
}
}

namespace dialogs {

class SelectSignalDialog : public QDialog
{
	Q_OBJECT

public:
	SelectSignalDialog(const Session &session,
		const shared_ptr<sv::devices::BaseDevice> expanded_device,
		QWidget *parent = nullptr);

	vector<shared_ptr<sv::data::BaseSignal>> signals();

private:
	void setup_ui();

	const Session &session_;
	const shared_ptr<sv::devices::BaseDevice> expanded_device_;
	vector<shared_ptr<sv::data::BaseSignal>> signals_;

	ui::devices::devicetree::DeviceTreeView *device_tree_;
	QDialogButtonBox *button_box_;

public Q_SLOTS:
	void accept() override;

};

} // namespace dialogs
} // namespace ui
} // namespace sv

#endif // UI_DIALOGS_SELECTSIGNALDIALOG_HPP
