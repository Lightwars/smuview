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

#ifndef CHANNELS_DIVIDECHANNEL_HPP
#define CHANNELS_DIVIDECHANNEL_HPP

#include <memory>
#include <mutex>
#include <set>
#include <string>

#include <QObject>

#include "src/channels/basechannel.hpp"
#include "src/channels/mathchannel.hpp"
#include "src/data/datautil.hpp"

using std::mutex;
using std::set;
using std::shared_ptr;
using std::string;

namespace sv {

namespace data {
class AnalogTimeSignal;
}

namespace devices {
class BaseDevice;
}

namespace channels {

class DivideChannel : public MathChannel
{
	Q_OBJECT

public:
	DivideChannel(
		data::Quantity quantity,
		const set<data::QuantityFlag> &quantity_flags,
		data::Unit unit,
		shared_ptr<data::AnalogTimeSignal> dividend_signal,
		shared_ptr<data::AnalogTimeSignal> divisor_signal,
		shared_ptr<devices::BaseDevice> parent_device,
		const set<string> &channel_group_names,
		const string &channel_name,
		double channel_start_timestamp);

private:
	shared_ptr<data::AnalogTimeSignal> dividend_signal_;
	shared_ptr<data::AnalogTimeSignal> divisor_signal_;
	size_t dividend_signal_pos_;
	size_t divisor_signal_pos_;
	mutex sample_append_mutex_;

private Q_SLOTS:
	void on_sample_appended();

};

} // namespace channels
} // namespace sv

#endif // CHANNELS_DIVIDECHANNEL_HPP
