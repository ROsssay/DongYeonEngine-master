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
    mLogoImage = new Gdiplus::Image(L"resources/TitleLogo.png");

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

    // ��׶��� �̹��� �׸���
    float bgImgWidth = static_cast<float>(mBackgroundImage->GetWidth());
    float bgImgHeight = static_cast<float>(mBackgroundImage->GetHeight());

    // �����ϸ� ���� ��� (â�� �°� ���)
    float scaleX = static_cast<float>(1280 / bgImgWidth);
    float scaleY = static_cast<float>(720 / bgImgHeight);
    float backGroundScale = min(scaleX, scaleY); // �� ���� ���� ���� (â �ȿ� ����)

    // �̹����� â���� ���� ��� ���� ũ�� ����
    if (backGroundScale > 1.0f) backGroundScale = 1.0f;

    // �� �̹��� ũ�� ���
    int destWidth = static_cast<int>(bgImgWidth * backGroundScale);
    int destHeight = static_cast<int>(bgImgHeight * backGroundScale);

    // �߾� ������ ���� ������
    int destX = (1280 - destWidth) / 2;
    int destY = (720 - destHeight) / 2;

    // ��׶��� �̹��� �׸���
    graphics.DrawImage(mBackgroundImage, destX, destY, destWidth, destHeight);

    // �ΰ� �̹��� �׸���
    float logoWidth = static_cast<float>(mLogoImage->GetWidth());
    float logoHeight = static_cast<float>(mLogoImage->GetHeight());

    // �ΰ� �̹����� �߾ӿ� ��ġ (���ϴ� ��ġ�� ���� ����)
    int logoX = (1280 - static_cast<int>(logoWidth)) / 2;  // �ΰ� ���� �߾ӿ�
    int logoY = ((720 - static_cast<int>(logoHeight)) / 2 ) - 100;  // �ΰ� ���� �߾ӿ�

    // �ΰ� �̹��� �׸��� (���� ũ�� ����)
    graphics.DrawImage(mLogoImage, logoX, logoY + 100, static_cast<int>(logoWidth), static_cast<int>(logoHeight));

    TextOut(hdc, 1280 / 2, 200, L"�����̽��ٸ� ���� ���� ȭ������ �Ѿ����", 23);

}