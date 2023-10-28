/*
This file is part of rabbitGram Desktop,
the unofficial app based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/rabbitGramDesktop/rabbitGramDesktop/blob/dev/LEGAL
*/
#pragma once

#include "settings/settings_type.h"

enum class PremiumPreview;

namespace ChatHelpers {
class Show;
} // namespace ChatHelpers

namespace Ui {
class RpWidget;
class GradientButton;
} // namespace Ui

namespace Main {
class Session;
} // namespace Main

namespace Window {
class SessionController;
} // namespace Window

namespace Settings {

[[nodiscard]] Type PremiumId();

void ShowPremium(not_null<::Main::Session*> session, const QString &ref);
void ShowPremium(
	not_null<Window::SessionController*> controller,
	const QString &ref);
void ShowGiftPremium(
	not_null<Window::SessionController*> controller,
	not_null<PeerData*> peer,
	int months,
	bool me);
void ShowEmojiStatusPremium(
	not_null<Window::SessionController*> controller,
	not_null<PeerData*> peer);

void StartPremiumPayment(
	not_null<Window::SessionController*> controller,
	const QString &ref);

[[nodiscard]] QString LookupPremiumRef(PremiumPreview section);

void ShowPremiumPromoToast(
	std::shared_ptr<ChatHelpers::Show> show,
	TextWithEntities textWithLink,
	const QString &ref);

struct SubscribeButtonArgs final {
	Window::SessionController *controller = nullptr;
	not_null<Ui::RpWidget*> parent;
	Fn<QString()> computeRef;
	std::optional<rpl::producer<QString>> text;
	std::optional<QGradientStops> gradientStops;
	Fn<QString()> computeBotUrl; // nullable
	std::shared_ptr<ChatHelpers::Show> show;
};

[[nodiscard]] not_null<Ui::GradientButton*> CreateSubscribeButton(
	SubscribeButtonArgs &&args);

[[nodiscard]] std::vector<PremiumPreview> PremiumPreviewOrder(
	not_null<::Main::Session*> session);


} // namespace Settings

