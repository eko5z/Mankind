#include "GUILabel.hpp"

#include "Log.hpp"

/* Because text is rendered with SDL_TTF,
   the Y-coordinate must be reversed */
#define UV_BOTTOM_LEFT  {0, 1}
#define UV_BOTTOM_RIGHT {1, 1}
#define UV_TOP_LEFT     {0, 0}
#define UV_TOP_RIGHT    {1, 0}

GUILabel::GUILabel(std::string id, glm::vec2 pos, glm::vec2 screen_dim,
                   std::shared_ptr<Font> font, std::string fmt, ...) :
	BaseGUIElement::BaseGUIElement(id),
	font(std::move(font)),
	fg_color(
{
	255, 255, 255, 255
}),
dirty(true),
pos(pos),
screen_dim(screen_dim)
{
	std::cerr << "pos = " << pos.x << ", " << pos.y << std::endl;
	this->pos.x = -1 + ((float)pos.x / screen_dim.x * 2.);
	this->pos.y = -1 + ((float)pos.y / screen_dim.y * 2.);
	va_list fmt_list;
	va_start(fmt_list, fmt);
	SetText(fmt, fmt_list);
	va_end(fmt_list);
	Reload();
}

void GUILabel::SetText(std::string fmt, va_list vl)
{
	va_list vl2;
	va_copy(vl2, vl);
	dirty = true;
	size_t text_size = vsnprintf(nullptr, 0, fmt.c_str(), vl);
	char *tmp_str = new char[text_size+1]();
	vsnprintf(tmp_str, text_size+1, fmt.c_str(), vl2);
	text = std::string(tmp_str);
	delete[] tmp_str;
}

void GUILabel::SetText(std::string fmt, ...)
{
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
	glm::vec2 wh{
		text_surface->w / screen_dim.x * 2,
		text_surface->h / screen_dim.y * 2};
	SDL_FreeSurface(text_surface);

	/* 0 - 1
	   | / |
	   2 - 3
	*/
	std::vector<glm::vec3> vertices(6, {0, 0, 0});

	for (auto& v : vertices) {
		v += glm::vec3(pos.x, pos.y, 0.f);
	}
	vertices[0] += glm::vec3(0.f, wh.y, 0.f);
	vertices[1] += glm::vec3(wh.x, wh.y, 0.f);
	vertices[2] += glm::vec3(0.f, 0.f, 0.f);

	vertices[3] += glm::vec3(0.f, 0.f, 0.f);
	vertices[4] += glm::vec3(wh.x, wh.y, 0.f);
	vertices[5] += glm::vec3(wh.x, 0.f, 0.f);

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
}

void GUILabel::Draw()
{
	if (dirty) {
		Reload();
	}
	glEnable(GL_BLEND);
	BaseGUIElement::Draw();
	glDisable(GL_BLEND);
}

