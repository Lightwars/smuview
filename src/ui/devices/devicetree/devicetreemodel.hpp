/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2019-2021 Frank Stettner <frank-stettner@gmx.net>
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

#ifndef UI_DEVICES_DEVICETREE_DEVICETREEMODEL_HPP
#define UI_DEVICES_DEVICETREE_DEVICETREEMODEL_HPP

#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <vector>

#include <QStandardItem>
#include <QStandardItemModel>

using std::set;
using std::shared_ptr;
using std::string;
using std::vector;

namespace sv {

class Session;

namespace channels {
class BaseChannel;
}
namespace data {
class BaseSignal;
namespace properties {
class BaseProperty;
}
}
namespace devices {
class BaseDevice;
class Configurable;
}

namespace ui {
namespace devices {
namespace devicetree {

class TreeItem;

class DeviceTreeModel : public QStandardItemModel
{
	Q_OBJECT

public:
	explicit DeviceTreeModel(const Session &session,
		bool is_device_checkable, bool is_channel_group_checkable,
		bool is_channel_checkable, bool is_signal_checkable,
		bool is_configurable_checkable, bool is_config_key_checkable,
		bool show_configurable, QObject *parent = nullptr);

	TreeItem *find_device(shared_ptr<sv::devices::BaseDevice> device) const;

	const static int DataRole = Qt::UserRole + 1;
	const static int SortRole = Qt::UserRole + 2;

private:
	void setup_model();

	void add_device(shared_ptr<sv::devices::BaseDevice> device);
	TreeItem *add_channel_group(
		const string &channel_group_name, TreeItem *device_item);
	void add_channel(shared_ptr<sv::channels::BaseChannel> channel,
		const set<string> &channel_group_names, TreeItem *parent_item);
	void add_signal(shared_ptr<sv::data::BaseSignal> signal,
		TreeItem *parent_item);
	void add_configurable(shared_ptr<sv::devices::Configurable> configurable,
		TreeItem *device_item);
	void add_property(shared_ptr<sv::data::properties::BaseProperty> property,
		TreeItem *configurable_item);

	TreeItem *find_channel_group(const string &channel_group_name,
		TreeItem *parent_item) const;
	TreeItem *find_channel(shared_ptr<sv::channels::BaseChannel> channel,
		const set<string> &channel_group_names, TreeItem *parent_item) const;
	TreeItem *find_signal(shared_ptr<sv::data::BaseSignal> signal,
		TreeItem *parent_item) const;
	TreeItem *find_configurable(
		shared_ptr<sv::devices::Configurable> configurable,
		TreeItem *device_item) const;
	TreeItem *find_property(
		shared_ptr<sv::data::properties::BaseProperty> property,
		TreeItem *configurable_item) const;

	const Session &session_;
	bool is_device_checkable_;
	bool is_channel_group_checkable_;
	bool is_channel_checkable_;
	bool is_signal_checkable_;
	bool is_configurable_checkable_;
	bool is_config_key_checkable_;
	bool show_configurable_;
	std::recursive_mutex mutex_;

private Q_SLOTS:
	void on_device_added(shared_ptr<sv::devices::BaseDevice> device);
	void on_device_removed(shared_ptr<sv::devices::BaseDevice> device);
	void on_channel_added(shared_ptr<sv::channels::BaseChannel> channel);
	void on_channel_removed(shared_ptr<sv::channels::BaseChannel> channel);
	void on_signal_added(shared_ptr<sv::data::BaseSignal> signal);
	void on_signal_removed(shared_ptr<sv::data::BaseSignal> signal);

};

} // namespace devicetree
} // namespace devices
} // namespace ui
} // namespace sv

#endif // UI_DEVICES_DEVICETREE_DEVICETREEMODEL_HPP
