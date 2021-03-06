/* ============================================================
 *
 * This file is a part of the rtt-rsb-transport project
 *
 * Copyright (C) 2016 Jan Moringen <jmoringe@techfak.uni-bielefeld.de>
 *
 * This file may be licensed under the terms of the
 * GNU Lesser General Public License Version 3 (the ``LGPL''),
 * or (at your option) any later version.
 *
 * Software distributed under the License is distributed
 * on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
 * express or implied. See the LGPL for the specific language
 * governing rights and limitations.
 *
 * You should have received a copy of the LGPL along with this
 * program. If not, go to http://www.gnu.org/licenses/lgpl.html
 * or write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The development of this software was supported by:
 *   CoR-Lab, Research Institute for Cognition and Robotics
 *     Bielefeld University
 *
 * ============================================================ */

#include "OutgoingChannelElement.hpp"

#include <rtt/TaskContext.hpp>

#include <rsc/runtime/TypeStringTools.h>

#include <rsb/Factory.h>

#include "../../util.hpp"

namespace rtt_rsbcomm {
namespace transport {
namespace socket {

OutgoingChannelElementBase::OutgoingChannelElementBase(RTT::base::PortInterface *port,
                                                       const RTT::ConnPolicy    &policy)
    : scope(policy.name_id) {
    RTT::Logger::In in(this->scope.toString());

    RTT::log(RTT::Debug)
        << "Creating RSB informer for port `"
        <<  displayNameForPort(port)
        << "' on scope " << this->scope
        << RTT::endlog();

    this->informer = rsb::getFactory().createInformer<rsb::AnyType>(this->scope);

    act = RSBPublishActivity::Instance();
    act->addPublisher(this);
}

OutgoingChannelElementBase::~OutgoingChannelElementBase() {
    RTT::Logger::In in(this->scope.toString());

    RTT::log(RTT::Debug)
        << "Destroying " << rsc::runtime::typeName(*this)
        << " on scope " << this->scope
        << RTT::endlog();
    act->removePublisher(this);
}

bool OutgoingChannelElementBase::inputReady() {
    return true;
}

}
}
}
