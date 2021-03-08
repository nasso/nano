/// <reference types="@types/emscripten" />

declare type EnumClass = unknown;

declare interface Deletable {
  delete(): void;
}

type Ref<T extends Deletable> = {
  [K in keyof T as Exclude<K, "delete">]: T[K];
}

interface UserImpl<T> extends T {
  __construct(): void;
  __destruct(): void;
}

type InterfaceBinding<T> = {
  extend(name: string, impl: UserImpl<T>): typeof T;
  implement(impl: UserImpl<T>): T;
};

declare class Vector<T> implements Deletable {
  constructor();

  size(): number;
  get(index: number): T;
  set(index: number, value: T): void;
  push_back(value: T): void;
  resize(newsize: number, newvalues: T): void;
  delete(): void;
}

declare class Map<K, V> implements Deletable {
  constructor();

  size(): number;
  get(key: K): V;
  set(key: K, value: V): void;
  keys(): Vector<K>;
  delete(): void;
}

export declare type PinId = number;
export declare type PinMode = EnumClass;
export declare type Tristate = EnumClass;

export declare type Pinout = Map<PinId, PinMode>;

export declare type Option<T> = null | T;

export declare interface IComponent {
  readonly stable: boolean;

  tick(): void;
  pinout(): Ref<Pinout>;
  read(pin: PinId): Tristate;
  write(pin: PinId, value: Tristate): void;
}

export declare abstract class AComponent implements IComponent, Deletable {
  readonly stable: boolean;

  pinout(): Ref<Pinout>;
  pinMode(pin: PinId, mode: PinMode): void;
  read(pin: PinId): Tristate;
  write(pin: PinId, value: Tristate): void;
  delete(): void;
}

export declare class Circuit extends AComponent {
  readonly stable: boolean;

  tick(): void;
  insert(name: string, comp: IComponent): void;
  remove(name: string): IComponent;
  get(name: string): undefined | IComponent;
  connect(chip1: string, pin1: PinId, chip2: string, pin2: PinId): void;
  connect(pin: PinId, chip: string, chipPin: PinId): void;
  connect(pin1: PinId, pin2: PinId): void;
  disconnect(chip1: string, pin1: PinId, chip2: string, pin2: PinId): void;
  disconnect(pin: PinId, chip: string, chipPin: PinId): void;
  disconnect(pin1: PinId, pin2: PinId): void;
  delete(): void;
}

export declare interface IComponentFactory {
  createComponent(name: string): Option<IComponent>;
}

export
declare class ComboComponentFactory implements IComponentFactory, Deletable {
  constructor();

  createComponent(name: string): Option<IComponent>;
  add(factory: IComponentFactory): void;
  delete(): void;
}

export
declare class BuiltInComponentFactory implements IComponentFactory, Deletable {
  constructor();

  createComponent(name: string): Option<IComponent>;
  delete(): void;
}

export declare class NtsCircuit extends Circuit {
  constructor();
}

export declare interface NtsModule extends EmscriptenModule {
  readonly Tristate: {
    UNDEFINED: Tristate,
    TRUE: Tristate,
    FALSE: Tristate,
  };
  readonly PinMode: {
    NONE: PinMode,
    INPUT: PinMode,
    OUTPUT: PinMode,
  };
  readonly Pinout: typeof Pinout,
  readonly IComponent: typeof IComponent,
  readonly AComponent: typeof AComponent,
  readonly Circuit: typeof Circuit,
  readonly IComponentFactory: Interface<IComponentFactory>,
  readonly ComboComponentFactory: typeof ComboComponentFactory,
  readonly BuiltInComponentFactory: typeof BuiltInComponentFactory,
  readonly NtsCircuit: typeof NtsCircuit,
}

declare const factory: EmscriptenModuleFactory<NtsModule>;

export default factory;
