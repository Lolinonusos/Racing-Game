// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerBoostWidget.h"

#include "Components/TextBlock.h"

bool UTimerBoostWidget::Initialize()
{
	Super::Initialize();
	FString TimeBoostOutput = "+";
	TimeBoostOutput.Append(FString::FromInt(TimeIncrease));
	TimeBoostOutput.Append(" Seconds");
	TimeText->SetText(FText::FromString(TimeBoostOutput));
	
	return true;
}

