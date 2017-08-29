# include <Siv3D.hpp>

void Main()
{
	Window::Resize(280, 280);

	Image image(280, 280, Palette::Black);
	Image dstImage(28 * 7, 28 * 4, Palette::Black);
	Image temp(28, 28, Palette::Black);;

	DynamicTexture texture(image);

	Array<Image> alhpabet;
	int32 alphabets = 28;
	int32 count = 0;

	while (System::Update())
	{
		//マウスの左クリックで描画
		if (Input::MouseL.pressed)
		{
			Line(Mouse::PreviousPos(), Mouse::Pos()).overwrite(image, 30, Palette::White);

			texture.fill(image.gaussianBlurred(15,15));
		}

		//NキーでArrayにImageを追加と表示のImageを真っ黒に
		if (Input::KeyN.pressed)
		{
			alhpabet.push_back(image.gaussianBlurred(15, 15));
			image = Image(Window::Size(), Palette::Black);
			texture.fill(image);
		}

		//Cキーで表示をクリアに
		if (Input::KeyC.pressed)
		{
			image = Image(Window::Size(), Palette::Black);
			texture.fill(image);
		}

		//SキーでArrayにあるImageを合わせて保存
		if (Input::KeyS.pressed) 
		{

			int i = 0, j = 0;
			for (auto it = alhpabet.begin(); it != alhpabet.end(); it++) 
			{
				temp = (*it).scaled(28, 28);
				dstImage.overwrite(temp, { 28 * i, 28 * j });
				i++;
				count++;
				if (i == 6) {
					j++;
					i = 0;
				}

			}
			

			dstImage.save(L"./juliamo_alphabet.png");
		}

		texture.draw();
	}
}