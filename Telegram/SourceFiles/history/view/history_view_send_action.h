/*
This file is part of rabbitGram Desktop,
the unofficial app based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/rabbitgramdesktop/rabbitgramdesktop/blob/dev/LEGAL
*/
#pragma once

#include "ui/effects/send_action_animations.h"
#include "api/api_send_progress.h"

class UserData;

namespace Main {
class Session;
} // namespace Main

namespace Data {
class ForumTopic;
} // namespace Data

namespace Api {
enum class SendProgressType;
struct SendProgress;
} // namespace Api

namespace HistoryView {

class SendActionPainter final {
public:
	explicit SendActionPainter(not_null<History*> history, MsgId rootId = 0);

	void setTopic(Data::ForumTopic *topic);

	bool paint(
		Painter &p,
		int x,
		int y,
		int availableWidth,
		int outerWidth,
		style::color color,
		crl::time now);
	void paintSpeaking(
		QPainter &p,
		int x,
		int y,
		int outerWidth,
		style::color color,
		crl::time now);

	bool updateNeedsAnimating(
		crl::time now,
		bool force = false);
	bool updateNeedsAnimating(
		not_null<UserData*> user,
		const MTPSendMessageAction &action);
	void clear(not_null<UserData*> from);

private:
	const not_null<History*> _history;
	const MsgId _rootId = 0;
	const base::weak_ptr<Main::Session> _weak;
	const style::TextStyle &_st;
	Data::ForumTopic *_topic = nullptr;
	base::flat_map<not_null<UserData*>, crl::time> _typing;
	base::flat_map<not_null<UserData*>, crl::time> _speaking;
	base::flat_map<not_null<UserData*>, Api::SendProgress> _sendActions;
	QString _sendActionString;
	Ui::Text::String _sendActionText;
	Ui::SendActionAnimation _sendActionAnimation;
	Ui::SendActionAnimation _speakingAnimation;

	int _animationLeft = 0;
	int _spacesCount = 0;

};

} // namespace HistoryView
