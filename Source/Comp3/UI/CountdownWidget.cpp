// Fill out your copyright notice in the Description page of Project Settings.


#include "CountdownWidget.h"
#include "GameHUD.h"

bool UCountdownWidget::Initialize() {
	Super::Initialize();

	Light1->SetBrushFromTexture(BlackLight, true);
	Light2->SetBrushFromTexture(BlackLight, true);
	Light3->SetBrushFromTexture(BlackLight, true);

	
		
	return true;
}

void UCountdownWidget::ChangeColorAndTime() {
	if (!CountdownInstancePtr) {
		CountdownInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}
	TimerSeconds++;
	switch (TimerSeconds) {
	case 1:
		Light1->SetBrushFromTexture(RedLight, true);
		UGameplayStatics::PlaySound2D(GetWorld(), NextSecond, CountdownInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
		break;
	case 2:
		Light2->SetBrushFromTexture(YellowLight, true);
		break;
	case 3:
		Light3->SetBrushFromTexture(GreenLight, true);
		break;
	case 4:
		Light2->SetBrushFromTexture(GreenLight, true);
		Light1->SetBrushFromTexture(GreenLight, true);
		Light3->SetBrushFromTexture(GreenLight, true);
		break;
	default:
		break;
	}
	
}


void UCountdownWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
	
}

