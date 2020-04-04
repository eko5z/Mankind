#include "GUILabel.hpp"

#include "Log.hpp"

#define VX_BOTTOM_LEFT  {-1, -1, 0}
#define VX_BOTTOM_RIGHT { 1, -1, 0}
#define VX_TOP_LEFT     {-1,  1, 0}
#define VX_TOP_RIGHT    { 1,  1, 0}

#define UV_BOTTOM_LEFT  {0, 0}
#define UV_BOTTOM_RIGHT {1, 0}
#define UV_TOP_LEFT     {0, 1}
#define UV_TOP_RIGHT    {1, 1}

GUILabel::GUILabel(std::string id, glm::vec2 pos, glm::vec2 screen_dim,
                   std::shared_ptr<Font> font, std::string fmt, ...) :
	BaseGUIElement::BaseGUIElement(id),
	font(std::move(font)),
	fg_color( {
	0, 0, 0, 255
}),
dirty(true),
      pos(pos),
      screen_dim(screen_dim)
{
	va_list fmt_list;
	va_start(fmt_list, fmt);
	SetText(fmt, fmt_list);
	va_end(fmt_list);
	Reload();
}

void GUILabel::SetText(std::string fmt, va_list vl)
{
	size_t text_size = vsnprintf(nullptr, 0, fmt.c_str(), vl);
	char *tmp_str = new char[text_size+1] {0};
	vsnprintf(tmp_str, text_size+1, fmt.c_str(), vl);
	text = std::string(tmp_str);
	delete tmp_str;
}

void GUILabel::SetText(std::string fmt, ...)
{
	dirty = true;
	va_list fmt_list;
	va_start(fmt_list, fmt);
	SetText(fmt, fmt_list);
	va_end(fmt_list);
}

void GUILabel::SetFont(std::shared_ptr<Font> font)
{
	dirty = true;
	this->font = std::move(font);
}

void GUILabel::SetForegroundColor(SDL_Color new_color)
{
	dirty = true;
	fg_color = new_color;
}

void GUILabel::Reload()
{
	dirty = false;
	SDL_Surface* text_surface = TTF_RenderText_Blended(font->GetPointer(), text.c_str(), fg_color);
	std::shared_ptr<Texture> fg_texture = std::make_shared<Texture>(text_surface);
	SDL_FreeSurface(text_surface);

	/* 0 - 1
	   | / |
	   2 - 3
	*/
	std::vector<glm::vec3> vertices{
		VX_TOP_LEFT,
		VX_TOP_RIGHT,
		VX_BOTTOM_LEFT,

		VX_BOTTOM_LEFT,
		VX_TOP_RIGHT,
		VX_BOTTOM_RIGHT
	};
	std::vector<glm::vec2> uvs{
		UV_TOP_LEFT,
		UV_TOP_RIGHT,
		UV_BOTTOM_LEFT,

		UV_BOTTOM_LEFT,
		UV_TOP_RIGHT,
		UV_BOTTOM_RIGHT
	};
	std::vector<GLuint> indices {
		0, 1, 2, 3, 4, 5
	};
	std::vector<glm::vec3> normals(6, glm::vec3(0, 0, -1));

	foreground = std::make_unique<Mesh>(vertices, normals, uvs, indices, fg_texture, nullptr);
	foreground->Initialize();
}

void GUILabel::Draw()
{
	if (dirty) {
		Reload();
	}
	BaseGUIElement::Draw();
}

