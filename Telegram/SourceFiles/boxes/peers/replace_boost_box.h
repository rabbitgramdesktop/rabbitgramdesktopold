/*
This file is part of rabbitGram Desktop,
the unofficial app based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/rabbitgramdesktop/rabbitgramdesktop/blob/dev/LEGAL
*/
#pragma once

#include "base/object_ptr.h"

class ChannelData;

namespace Main {
class Session;
} // namespace Main

namespace Ui {
struct BoostCounters;
struct BoostFeatures;
class BoxContent;
class RpWidget;
} // namespace Ui

struct TakenBoostSlot {
	int id = 0;
	TimeId expires = 0;
	PeerId peerId = 0;
	TimeId cooldown = 0;
};

struct ForChannelBoostSlots {
	std::vector<int> free;
	std::vector<int> already;
	std::vector<TakenBoostSlot> other;
};

[[nodiscard]] ForChannelBoostSlots ParseForChannelBoostSlots(
	not_null<ChannelData*> channel,
	const QVector<MTPMyBoost> &boosts);

[[nodiscard]] Ui::BoostCounters ParseBoostCounters(
	const MTPpremium_BoostsStatus &status);

[[nodiscard]] Ui::BoostFeatures LookupBoostFeatures(
	not_null<ChannelData*> channel);

[[nodiscard]] int BoostsForGift(not_null<Main::Session*> session);

object_ptr<Ui::BoxContent> ReassignBoostsBox(
	not_null<ChannelData*> to,
	std::vector<TakenBoostSlot> from,
	Fn<void(std::vector<int> slots, int groups, int channels)> reassign,
	Fn<void()> cancel);

[[nodiscard]] object_ptr<Ui::RpWidget> CreateBoostReplaceUserpics(
	not_null<Ui::RpWidget*> parent,
	rpl::producer<std::vector<not_null<PeerData*>>> from,
	not_null<PeerData*> to);
