/*
This file is part of exteraGram Desktop,
the unofficial app based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/xmdnx/exteraGramDesktop/blob/dev/LEGAL
*/
#include <ui/boxes/single_choice_box.h>

#include "extera/extera_settings.h"
#include "extera/extera_lang.h"
#include "extera/extera_settings_menu.h"
#include "lang_auto.h"
#include "mainwindow.h"
#include "settings/settings_common.h"
#include "ui/wrap/vertical_layout.h"
#include "ui/wrap/slide_wrap.h"
#include "ui/widgets/buttons.h"
#include "ui/widgets/labels.h"
#include "ui/widgets/checkbox.h"
#include "boxes/connection_box.h"
#include "platform/platform_specific.h"
#include "window/window_session_controller.h"
#include "lang/lang_instance.h"
#include "core/application.h"
#include "storage/localstorage.h"
#include "data/data_session.h"
#include "main/main_session.h"
#include "styles/style_settings.h"
#include "apiwrap.h"
#include "api/api_blocked_peers.h"
#include "ui/widgets/continuous_sliders.h"

#define SettingsMenuJsonSwitch(LangKey, Option) AddButton( \
	container, \
	rktr(#LangKey), \
	st::settingsButtonNoIcon \
)->toggleOn( \
	rpl::single(::ExteraSettings::JsonSettings::GetBool(#Option)) \
)->toggledValue( \
) | rpl::filter([](bool enabled) { \
	return (enabled != ::ExteraSettings::JsonSettings::GetBool(#Option)); \
}) | rpl::start_with_next([](bool enabled) { \
	::ExteraSettings::JsonSettings::Set(#Option, enabled); \
	::ExteraSettings::JsonSettings::Write(); \
}, container->lifetime());

namespace Settings {

    rpl::producer<QString> Extera::title() {
        return rktr("etg_settings_extera");
    }

    Extera::Extera(
            QWidget *parent,
            not_null<Window::SessionController *> controller)
            : Section(parent) {
        setupContent(controller);
    }

	void Extera::SetupGeneral(not_null<Ui::VerticalLayout *> container)
    {
	    AddSubsectionTitle(container, rktr("etg_settings_general"));

    	SettingsMenuJsonSwitch(etg_settings_show_phone_number, show_phone_in_settings);
    	SettingsMenuJsonSwitch(etg_settings_chat_id, show_ids);
    }

    void Extera::SetupChats(not_null<Ui::VerticalLayout *> container) {
        AddSubsectionTitle(container, rktr("etg_settings_chats"));
    	
        const auto stickerHeightLabel = container->add(
		    object_ptr<Ui::LabelSimple>(
			    container,
			    st::settingsAudioVolumeLabel),
		    st::settingsAudioVolumeLabelPadding);
	    const auto stickerHeightSlider = container->add(
		    object_ptr<Ui::MediaSlider>(
			    container,
			    st::settingsAudioVolumeSlider),
		    st::settingsAudioVolumeSliderPadding);
	    const auto updateStickerHeightLabel = [=](int value) {
		    const auto pixels = QString::number(value);
		    stickerHeightLabel->setText(ktr("etg_settings_sticker_height", { "pixels", pixels }));
	    };
	    const auto updateStickerHeight = [=](int value) {
		    updateStickerHeightLabel(value);
		    ::ExteraSettings::JsonSettings::Set("sticker_height", value);
		    ::ExteraSettings::JsonSettings::Write();
	    };
	    stickerHeightSlider->resize(st::settingsAudioVolumeSlider.seekSize);
	    stickerHeightSlider->setPseudoDiscrete(
		    193,
		    [](int val) { return val + 64; },
		    ::ExteraSettings::JsonSettings::GetInt("sticker_height"),
		    updateStickerHeight);
	    updateStickerHeightLabel(::ExteraSettings::JsonSettings::GetInt("sticker_height"));
    }

    void Extera::SetupExteraSettings(not_null<Ui::VerticalLayout *> container, not_null<Window::SessionController *> controller) {
		AddSkip(container);
    	SetupGeneral(container);

    	AddSkip(container);
        SetupChats(container);
    }

    void Extera::setupContent(not_null<Window::SessionController *> controller) {
        const auto content = Ui::CreateChild<Ui::VerticalLayout>(this);

        SetupExteraSettings(content, controller);

        Ui::ResizeFitChild(this, content);
    }
} // namespace Settings
