/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2012 Joel Holdsworth <joel@airwebreathe.org.uk>
 * Copyright (C) 2016 Soeren Apel <soeren@apelpie.net>
 * Copyright (C) 2016-2019 Frank Stettner <frank-stettner@gmx.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHANNELS_BASECHANNEL_HPP
#define CHANNELS_BASECHANNEL_HPP

#include <memory>
#include <set>
#include <string>
#include <utility>

#include <QObject>
#include <QSettings>
#include <QString>

#include "src/data/datautil.hpp"

using std::map;
using std::pair;
using std::set;
using std::shared_ptr;
using std::string;

namespace sv {

namespace data {
class BaseSignal;
}

namespace devices {
class BaseDevice;
}

namespace channels {

enum class ChannelType {
	/**
	 * Channels with analog data (Power supplies, loads, DMMs)
	 */
	AnalogChannel,
	/**
	 * Virtual channel generated by math operations
	 */
	UserChannel
};

class BaseChannel :
	public QObject,
	public std::enable_shared_from_this<BaseChannel>
{
	Q_OBJECT

public:
	BaseChannel(
		shared_ptr<devices::BaseDevice> parent_device,
		set<string> channel_group_names,
		double channel_start_timestamp);
	virtual ~BaseChannel();

public:
	// TODO: merge with Configurable::measured_quantity_t
	typedef pair<data::Quantity, set<data::QuantityFlag>> quantity_t;

	/**
	 * Returns enabled status of this channel.
	 */
	virtual bool enabled() const;

	/**
	 * Sets the enabled status of this channel.
	 * @param value Boolean value to set.
	 */
	virtual void set_enabled(bool value);

	/**
	 * Gets the type of this channel.
	 */
	ChannelType type() const;

	/**
	 * Gets the index number of this channel, i.e. a unique ID assigned by
	 * the device driver.
	 */
	virtual unsigned int index() const = 0;

	/**
	 * Does this channel have just one signal, thats quantity doesn't chege?
	 */
	bool has_fixed_signal();

	/**
	 * Sets if this channel has just one signal, thats quantity doesn't chege
	 */
	void set_fixed_signal(bool has_fixed_signal);

	/**
	 * Gets the actual signal
	 */
	shared_ptr<data::BaseSignal> actual_signal();

	/**
	 * Get all signals for this channel
	 */
	map<quantity_t, shared_ptr<data::BaseSignal>> signal_map();

	/**
	 * Delete all signals from this channel
	 */
	void clear_signals();

	/**
	 * Returns the device, this channel belongs to.
	 */
	shared_ptr<devices::BaseDevice> parent_device();

	/**
	 * Add a channel group name
	 */
	void add_channel_group_name(string channel_group_name);

	/**
	 * Get the channel group name, the channel is in. Returns "" if the channel
	 * is not in a channel group.
	 */
	set<string> channel_group_names() const;

	/**
	 * Gets the name of this channel, i.e. how the device calls it.
	 */
	string name() const;

	/**
	 * Sets the name of the signal.
	 */
	virtual void set_name(string name);

	/**
	 * Gets the display name of this channel.
	 */
	QString display_name() const;

	/**
	 * Inits a signal
	 *
	 * TODO: Implement here!
	 */
	/*
	virtual shared_ptr<data::BaseSignal> init_signal(
		data::Quantity quantity,
		set<data::QuantityFlag> quantity_flags,
		data::Unit unit) = 0;
	*/

	virtual void save_settings(QSettings &settings) const;
	virtual void restore_settings(QSettings &settings);

protected:
	ChannelType channel_type_;
	double channel_start_timestamp_;
	bool has_fixed_signal_;

	shared_ptr<data::BaseSignal> actual_signal_;
	map<quantity_t, shared_ptr<data::BaseSignal>> signal_map_;

	shared_ptr<devices::BaseDevice> parent_device_;
	set<string> channel_group_names_;
	string name_;

public Q_SLOTS:
	void on_aquisition_start_timestamp_changed(double);

Q_SIGNALS:
	void channel_start_timestamp_changed(double);
	void enabled_changed(const bool);
	void name_changed(const string);
	void signal_added(shared_ptr<sv::data::BaseSignal>);
	void signal_changed(shared_ptr<sv::data::BaseSignal>);

};

} // namespace channels
} // namespace sv

#endif // CHANNELS_BASECHANNEL_HPP
