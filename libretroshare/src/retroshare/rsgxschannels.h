/*******************************************************************************
 * libretroshare/src/retroshare: rsgxschannels.h                               *
 *                                                                             *
 * libretroshare: retroshare core library                                      *
 *                                                                             *
 * Copyright 2012-2012 by Robert Fernie <retroshare@lunamutt.com>              *
 *                                                                             *
 * This program is free software: you can redistribute it and/or modify        *
 * it under the terms of the GNU Lesser General Public License as              *
 * published by the Free Software Foundation, either version 3 of the          *
 * License, or (at your option) any later version.                             *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU Lesser General Public License for more details.                         *
 *                                                                             *
 * You should have received a copy of the GNU Lesser General Public License    *
 * along with this program. If not, see <https://www.gnu.org/licenses/>.       *
 *                                                                             *
 *******************************************************************************/
#ifndef RETROSHARE_GXS_CHANNEL_GUI_INTERFACE_H
#define RETROSHARE_GXS_CHANNEL_GUI_INTERFACE_H

#include <inttypes.h>
#include <string>
#include <list>

#include "retroshare/rstokenservice.h"
#include "retroshare/rsgxsifacehelper.h"
#include "retroshare/rsgxscommon.h"
#include "retroshare/rsturtle.h"

/* The Main Interface Class - for information about your Peers */
class RsGxsChannels;
extern RsGxsChannels *rsGxsChannels;


// These should be in rsgxscommon.h

class RsGxsChannelGroup
{
	public:
	RsGroupMetaData mMeta;
	std::string mDescription;
	RsGxsImage mImage;

	bool mAutoDownload;
};

class RsGxsChannelPost
{
public:
	RsGxsChannelPost() : mCount(0), mSize(0) {}

public:
	RsMsgMetaData mMeta;

    std::set<RsGxsMessageId> mOlderVersions ;
	std::string mMsg;  // UTF8 encoded.

	std::list<RsGxsFile> mFiles;
	uint32_t mCount;   // auto calced.
	uint64_t mSize;    // auto calced.

	RsGxsImage mThumbnail;
};


std::ostream &operator<<(std::ostream &out, const RsGxsChannelGroup &group);
std::ostream &operator<<(std::ostream &out, const RsGxsChannelPost &post);

class RsGxsChannels: public RsGxsIfaceHelper, public RsGxsCommentService
{
public:

	explicit RsGxsChannels(RsGxsIface *gxs)
	    :RsGxsIfaceHelper(gxs)  {}
	virtual ~RsGxsChannels() {}

	/* Specific Service Data */
	virtual bool getGroupData(const uint32_t &token, std::vector<RsGxsChannelGroup> &groups) = 0;
	virtual bool getPostData(const uint32_t &token, std::vector<RsGxsChannelPost> &posts, std::vector<RsGxsComment> &cmts) = 0;
	virtual bool getPostData(const uint32_t &token, std::vector<RsGxsChannelPost> &posts) = 0;

    //////////////////////////////////////////////////////////////////////////////
    ///                     Distant synchronisation methods                    ///
    //////////////////////////////////////////////////////////////////////////////
    ///
	virtual TurtleRequestId turtleGroupRequest(const RsGxsGroupId& group_id)=0;
	virtual TurtleRequestId turtleSearchRequest(const std::string& match_string)=0;
	virtual bool retrieveDistantSearchResults(TurtleRequestId req, std::map<RsGxsGroupId, RsGxsGroupSummary> &results) =0;
	virtual bool clearDistantSearchResults(TurtleRequestId req)=0;
	virtual bool retrieveDistantGroup(const RsGxsGroupId& group_id,RsGxsChannelGroup& distant_group)=0;

	//////////////////////////////////////////////////////////////////////////////
	virtual void setMessageReadStatus(uint32_t& token, const RsGxsGrpMsgIdPair& msgId, bool read) = 0;

	virtual bool setChannelAutoDownload(const RsGxsGroupId &groupId, bool enabled) = 0;
	virtual bool getChannelAutoDownload(const RsGxsGroupId &groupid, bool& enabled) = 0;

	virtual bool setChannelDownloadDirectory(const RsGxsGroupId &groupId, const std::string& directory)=0;
	virtual bool getChannelDownloadDirectory(const RsGxsGroupId &groupId, std::string& directory)=0;

	virtual bool groupShareKeys(const RsGxsGroupId &groupId, std::set<RsPeerId>& peers)=0;

	// Overloaded subscribe fn.
	virtual bool subscribeToGroup(uint32_t &token, const RsGxsGroupId &groupId, bool subscribe) = 0;

	virtual bool createGroup(uint32_t &token, RsGxsChannelGroup &group) = 0;
	virtual bool createPost(uint32_t &token, RsGxsChannelPost &post) = 0;

	virtual bool updateGroup(uint32_t &token, RsGxsChannelGroup &group) = 0;

	// File Interface
	virtual bool ExtraFileHash(const std::string &path, std::string filename) = 0;
	virtual bool ExtraFileRemove(const RsFileHash &hash) = 0;
};



#endif
