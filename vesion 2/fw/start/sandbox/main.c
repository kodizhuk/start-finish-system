/*START*/

	/*перевірка дозволу для старту наступного лижника*/
	bool ControlStartPermissionSkier(void);
	
	/*вкл індикацію дозволу старту лижника*/
	void IndicationStartAllowed(void);
	
	/*відображення дозволу старту лижника на дисплеї*/
	void DisplayIndicationStartAllowed(void);
	
	/*записати реальний час старту лижника */
	int WriteRealTimeStartSkier(uint16_t numberSkier);
	
	/*синзронізація даних про лижники із фінішом*/
	bool SyncDataWithFinish( SKIERRESULT_t *skierTime);
	
	/*зчитати команди із панелі управління/смартфона*/
	int ReadCommandcontrolPanel(void);	
int main(void)
{
}