/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <stdio.h>
#include <assert.h>

#include "peer_conn_event.h"

static const char * const peer_name[] = {
#define X(name) STRINGIFY(name),
	PEER_ID_LIST
#undef X
};

static int log_peer_conn_event(const struct event_header *eh, char *buf,
				  size_t buf_len)
{
	const struct peer_conn_event *event = cast_peer_conn_event(eh);

	BUILD_ASSERT(ARRAY_SIZE(peer_name) == PEER_ID_COUNT,
			 "Invalid number of elements");

	__ASSERT_NO_MSG(event->peer_id < PEER_ID_COUNT);

	EVENT_MANAGER_LOG(eh,
		"%s:%s_%d baud:%d",
		event->conn_state == PEER_STATE_CONNECTED ?
			"CONNECTED" : "DISCONNECTED",
		peer_name[event->peer_id],
		event->dev_idx,
		event->baudrate);
	return 0;
}

EVENT_TYPE_DEFINE(peer_conn_event,
		  IS_ENABLED(CONFIG_BRIDGE_LOG_PEER_CONN_EVENT),
		  log_peer_conn_event,
		  NULL);
