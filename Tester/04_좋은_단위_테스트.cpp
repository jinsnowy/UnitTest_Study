#include "pch.h"

class Message {
public:
	string Header;
	string Body;
	string Footer;
};

class IRender {
public:
	virtual string Render(Message message) abstract;
};

class HeaderRenderer : public IRender {
public:
	virtual string Render(Message message) override {
		char buf[128]; snprintf(buf, 128, "<h1>%s</h1>", message.Header.c_str());
		return buf;
	}
};

class BodyRenderer : public IRender {
public:
	virtual string Render(Message message) override {
		char buf[128]; snprintf(buf, 128, "<b>%s</b>", message.Body.c_str());
		return buf;
	}
};

class FooterRenderer : public IRender {
public:
	virtual string Render(Message message) override {
		char buf[128]; snprintf(buf, 128, "<i>%s</i>", message.Footer.c_str());
		return buf;
	}
};

class MessageRenderer : public IRender {
public:
	vector<IRender*> SubRenders;

	MessageRenderer() {
		SubRenders = {
			new HeaderRenderer(),
			new BodyRenderer(),
			new FooterRenderer()
		};
	}

	virtual string Render(Message message) override {
		stringstream ss;
		for (auto render : SubRenders) {
			ss << render->Render(message);
		}

		return ss.str();
	}
};

TEST(TestMessageRender, 메세지_렌더러의_서브_렌더러_유효함){
	MessageRenderer sut = {};
	auto& subRenderers = sut.SubRenders;

	ASSERT_EQ(3, subRenderers.size());
	ASSERT_TRUE(dynamic_cast<HeaderRenderer*>(subRenderers[0]) != nullptr);
	ASSERT_TRUE(dynamic_cast<BodyRenderer*>(subRenderers[1]) != nullptr);
	ASSERT_TRUE(dynamic_cast<FooterRenderer*>(subRenderers[2]) != nullptr);
}

TEST(TestMessageRender, 메세지_렌더러의_HTML_결과_유효함) {
	MessageRenderer sut = {};
	Message msg;
	msg.Header = "h";
	msg.Body = "b";
	msg.Footer = "f";

	string html = sut.Render(msg);

	ASSERT_EQ(html, "<h1>h</h1><b>b</b><i>f</i>");
}
