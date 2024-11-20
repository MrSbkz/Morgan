// Copyrights P.K.

#include "UI/MorganWeaponDataWidget.h"
#include "Components/MorganWeaponComponent.h"
#include "Components/TextBlock.h"
#include "Weapon/MorganPistolWeapon.h"

void UMorganWeaponDataWidget::BindToWeaponComponent(const UMorganWeaponComponent* WeaponComponent) const
{
	if (!WeaponComponent) return;
	
	if (AMorganPistolWeapon* PistolWeapon = Cast<AMorganPistolWeapon>(WeaponComponent->GetWeapon()))
	{
		BulletsLeftText->SetText(FText::FromString(FString::FromInt(PistolWeapon->GetBulletsAmount())));
		BulletsAmountText->SetText(FText::FromString(FString::FromInt(PistolWeapon->GetBulletsAmount())));
		PistolWeapon->OnBulletsUpdated.AddLambda([this](const int32 BulletsLeft)
		{
			BulletsLeftText->SetText(FText::FromString(FString::FromInt(BulletsLeft)));
		});
	}
}
