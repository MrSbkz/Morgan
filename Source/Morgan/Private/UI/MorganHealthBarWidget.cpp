// Copyrights P.K.

#include "UI/MorganHealthBarWidget.h"
#include "Components/ProgressBar.h"

void UMorganHealthBarWidget::SetHealth(const float HealthPercent) const
{
	HealthProgressBar->SetPercent(HealthPercent);
	if (HealthPercent > 0.6f)
	{
		HealthProgressBar->SetFillColorAndOpacity(GreenColor);
	}
	else if (HealthPercent > 0.2f && HealthPercent <= 0.6f)
	{
		HealthProgressBar->SetFillColorAndOpacity(YellowColor);
	}
	else
	{
		HealthProgressBar->SetFillColorAndOpacity(RedColor);
	}
}
