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

#ifndef UI_DATATYPES_BASEWIDEGT_HPP
#define UI_DATATYPES_BASEWIDEGT_HPP

#include <memory>

#include <QVariant>

using std::shared_ptr;

namespace sv {

namespace data {
namespace properties {
class BaseProperty;
}
}

namespace ui {
namespace datatypes {

class BaseWidget
{

public:
	BaseWidget(
		shared_ptr<sv::data::properties::BaseProperty> property,
		const bool auto_commit, const bool auto_update);

	virtual QVariant variant_value() const = 0;

protected:
	const bool auto_commit_;
	const bool auto_update_;
	shared_ptr<sv::data::properties::BaseProperty> property_;

/*
 * NOTE: With Qt, inheriting QObject twice (in the datatype widget classes) will
 *       cause problems in moc! Because of that, this class is not inherited
 *       from QObject and therefore no virtual Q_SLOTS in here!
 *       Also this eliminates the clang-tidy clang-analyzer-optin.cplusplus.VirtualCall
 *       warning.
 */
protected Q_SLOTS:
	/**
	 * Signal handling for Widget -> Property
	 * NOTE: No virtual method for value_changed, because every instance has an
	 *       other datatype for the parameter.
	 */
	//virtual void value_changed(const double value) = 0;

	/**
	 * Signal handling for Property -> Widget
	 * NOTE: No virtual method for on_value_changed.
	 */
	//virtual void on_value_changed(const QVariant &qvar) = 0;

	/**
	 * Signal handling for Property -> Widget
	 * NOTE: No virtual method for on_list_changed.
	 */
	//virtual void on_list_changed() = 0;

};

} // namespace datatypes
} // namespace ui
} // namespace sv

#endif // UI_DATATYPES_BASEWIDEGT_HPP
