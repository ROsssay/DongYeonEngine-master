#include "TitleScene.h"
#include "GameObject.h"
#include "SceneManager.h"

TitleScene::TitleScene()
    : mBackgroundImage(nullptr)
    , mGdiplusToken(0)
{
    // GDI+ �ʱ�ȭ
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartup(&mGdiplusToken, &gdiplusStartupInput, nullptr);
}

TitleScene::~TitleScene()
{
    if (mBackgroundImage != nullptr)
    {
        delete mBackgroundImage; // �̹��� ��ü ����
        mBackgroundImage = nullptr;
    }

    // GDI+ ����
    if (mGdiplusToken != 0)
    {
        Gdiplus::GdiplusShutdown(mGdiplusToken);
        mGdiplusToken = 0;
    }
}

void TitleScene::Initialize()
{

    mBackgroundImage = new Gdiplus::Image(L"resources/maintitle.png");
    if (mBackgroundImage->GetLastStatus() != Gdiplus::Ok) //�ε�ƴ��� �ȵƴ��� Ȯ��
    {
        MessageBox(NULL, L"Failed to load background.png", L"Error", MB_OK);

        delete mBackgroundImage;
        mBackgroundImage = nullptr;
    }

}

void TitleScene::Update()
{
    Scene::Update();

    // �����̽� Ű�� PlayScene ��ȯ
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        SceneManager::LoadScene(L"PlayScene");
    }
}

void TitleScene::LateUpdate()
{
    Scene::LateUpdate();
}

void TitleScene::Render(HDC hdc)
{
    Scene::Render(hdc);
    Gdiplus::Graphics graphics(hdc);

    // �̹��� ���� ũ��
    float imgWidth = static_cast<float>(mBackgroundImage->GetWidth());
    float imgHeight = static_cast<float>(mBackgroundImage->GetHeight());

    // �����ϸ� ���� ��� (â�� �°� ���)
    float scaleX = static_cast<float>(1280 / imgWidth);
    float scaleY = static_cast<float>(720 / imgHeight);
    float scale = min(scaleX, scaleY); // �� ���� ���� ���� (â �ȿ� ����)

    // �̹����� â���� ���� ��� ���� ũ�� ����
    if (scale > 1.0f) scale = 1.0f;

    // �� �̹��� ũ�� ���
    int destWidth = static_cast<int>(imgWidth * scale);
    int destHeight = static_cast<int>(imgHeight * scale);

    // �߾� ������ ���� ������
    int destX = (1280 - destWidth) / 2;
    int destY = (720 - destHeight) / 2;

    // �̹��� �׸���
    graphics.DrawImage(mBackgroundImage, 0, 0, destWidth, destHeight);

}